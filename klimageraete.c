// zum Abschalten unbedingt AUSKOMMENTIEREN, nicht auf 0 setzen oder so!
// #define DEBUG 1

// für die DB-Anbindung:
#include <my_global.h>
#include <mysql.h>

#include "lib/klimageraete-global.c"
#include "lib/klimageraete-core.c" // alles, was direkt die Verarbeitung des Typs "t_klimageraet" betrifft
#include "lib/klimageraete-mysql.c" // MySQL-bezogene Funktionen
#include "lib/klimageraete-suche.c"
#ifdef DEBUG
	#include "lib/klimageraete-test.c"
#endif

void init(void);
void destroy(void);
void hauptMenu(void); // Anzeige und Verarbeitung
void tabellenMenu(void); // Anzeige und Verarbeitung
void suchMenu(void); // Anzeige und Verarbeitung
void zeigeTabelle(void); // nur Anzeige
void neuesGeraet(); // interaktive Prozedur: neuen Datensatz anlegen
void ersetzeGeraet(); // interaktive Prozedur: Datensatz ersetzen
void aendereGeraet(); // interaktive Prozedur: Datensatz ändern
void loescheGeraet(); // interaktive Prozedur: Datensatz löschen

int main(int argc, char** argv) {
	init(); // definierten Start-Zustand herstellen

#ifdef DEBUG
	// debugPrintStatus();

	// testEingabeLeererInt();
	// testEingabeLeererPreis();
	// testEingabeLeererPreis();
	// warteAufTaste();
#endif

	hauptMenu(); // Haupt-Schleife, "Home-Screen" des Programms

	destroy(); // End-Zustand definiert behandeln (speichern?)

	return 0;
}

void init() {
	// printf("MySQL client version: %s\n", mysql_get_client_info()); exit(0);

	// MySQL-Verbindung:
	con = mysql_init(NULL);
	if (con == NULL) finishWithError(con);
	if (mysql_real_connect(con, DB_HOST, DB_USER, DB_PASS, NULL, 0, NULL, 0) == NULL) finishWithError(con);

	// Tabelle auswählen:
	char puffer[64]; puffer[0] = '\0'; char * p = &puffer[0];
	strcat(p, "USE "); strcat(p, DB_NAME); strcat(p, ";"); // "USE klimageraete;"
	if (mysql_query(con, p)) finishWithError(con);

	int i=0;
	for (i=0; i<MAX_GERAETE; i++) {
		klimageraete[i].modellBezeichnung[0] = '\0';
		filterKlimageraete[i] = FILTER_SICHTBAR;
	}

#ifdef DEBUG
	// legt einige Test-Datensätze an
	// initTest();
#endif

	// liest Klimageräte aus der Datenbank:
	klimageraeteFromDB(&klimageraete[0], MAX_GERAETE);


	// nur, wenn etwas schiefgegangen ist (?) - Datei lesen:
	if (nGeraete() > 0) return;

	// wenn Datenbank auf der Festplatte existiert, diese gleich wieder einlesen
	FILE * f = fopen("./klimageraete.dat", "r");
	if (f != NULL) {
		// Datensätze nacheinander einlesen
		for (i=0; ; i++) {
			// wenn Rückgabewert (Anzahl der tatsächlich gelesenen Datensätze...) anders als 1 --> abbrechen!
			if (fread(&klimageraete[i], sizeof klimageraete[0], 1, f) != 1) break;
		}
		fclose(f);
	}
}

void destroy() {
	// Bildschirm löschen, damit nicht das Menü stehen bleibt und
	// irritiert.
	cls();

	int i;

	// TODO: Wenn keine Datensätze vorhanden sind, Datei löschen.
	int erfolg = 0;
	FILE * f = fopen("./klimageraete.dat", "w");
	if (f != NULL) {
		// nur belegte Datensätze nacheinander schreiben
		for (i=0; i<MAX_GERAETE; i++) {
			if (!istFreiesGeraet(&klimageraete[i])) {
				fwrite(&klimageraete[i], sizeof klimageraete[0], 1, f);
			}
		}
		fclose(f);
		erfolg = -1;
	}

	// ... und in der MySQL-Datenbank speichern:

	// SQL-Befehl #1 - die Datenbank leeren:
	char puffer[1024]; puffer[0] = '\0'; char * p = &puffer[0];
	strcat(p, "DELETE FROM "); strcat(p, DB_TABLE);	strcat(p, ";");
	if (mysql_query(con, p)) finishWithError(con);

	for (i=0; i<MAX_GERAETE; i++) {
		if (istFreiesGeraet(&klimageraete[i])) continue;

		// gibt keinen Status zurück - im Fehlerfall wird das Programm
		// direkt beendet
		klimageraetToDB(&klimageraete[i]);
	}
	// Datenbank-Verbindung beenden:
	mysql_close(con);



	if (erfolg) {
		printf("Die Datenbank mit %d Klimageräten wurde gespeichert.\n", nGeraete());
	} else {
		fprintf(stderr, "Die Datenbank mit den Klimageräten konnte nicht gespeichert werden!\n");
	}
}

void hauptMenu() {
	int abbruch = 0;
	do {
		cls();

		printf("Hauptmenü\n");
		printf("\n");
		printf("* Es befinden sich aktuell %d Klimageräte in der Datenbank. *\n", nGeraete());
		printf("\n");
		printf("\t1\tEingabe\n");
		printf("\t2\tAusgabe\n");
		printf("\t3\tÄndern\n");
		printf("\t4\tErsetzen\n");
		printf("\t5\tLöschen\n");
		printf("\t6\tSuchen\n");
		printf("\n");
		printf("\t9\tBeenden\n");

		char * auswahl = textEingabeEinZeichenOhneEcho();
		switch(*auswahl) {
			case '1': // eingeben
				neuesGeraet();
				break;
			case '2': // ausgeben
				tabellenMenu();
				break;
			case '3': // update / ändern
				aendereGeraet();
				break;
			case '4': // ersetzen
				ersetzeGeraet();
				break;
			case '5': // löschen
				loescheGeraet();
				break;
			case '6': // suchen
				suchMenu();
				break;
			case '9': case 'q': case 'Q': case 'x': case 'X': case 27: case 0:
				abbruch = -1;
				break;
		}
	} while(!abbruch);
}

void zeigeTabelle() {
	if (nSichtbareGeraete() <= 0) {
		printf("   (Es gibt keine Suchergebnisse...)\n");
		return;
	}

	// Sonderfall: wenn nur eins vorhanden, direkt die Details anzeigen
	if (nSichtbareGeraete() == 1) {
		ausgabeKlimageraet( &klimageraete[ einzigesSichtbaresGeraet() ] );
		return;
	}

	printf("   # ");
	printKlimageraetZeilenUeberschrift();
	printf("     ");
	printKlimageraetZeilenUntertitel();
	printf("====|");
	printKlimageraetZeilenSeparator();

	int i;
	for (i=0; i<MAX_GERAETE; i++) {
		if (istFreiesGeraet(&klimageraete[i])) continue;
		if (filterKlimageraete[i] == FILTER_VERSTECKT) continue;
		printf("%4d ", i);
		printKlimageraetZeile(&klimageraete[i]);
	}

	printf("====|");
	printKlimageraetZeilenSeparator();
}

void suchMenu() {
	if (nGeraete() == 0) {
		cls();
		printf("Es sind keine Geräte zum Suchen vorhanden.\n\n");
		warteAufTaste();
		return;
	}

	int abbruch = 0;
	do {

		cls();

		printf("Suchen (Schritt 1)\n");
		printf("\n");
		printf("Nach welchem Kriterium wollen Sie suchen?");
		printf("\n");
		printf("\t1\tModellbezeichnung\n");
		printf("\t2\tKälteleistung\n");
		printf("\t3\tStromverbrauch\n");
		printf("\t4\tAbmessungen\n");
		printf("\t5\tPreis\n");
		printf("\n");
		printf("\t<RETURN>\tzurück\n");

		textEingabeAcceptEmpty = -1;
		char * auswahl = textEingabeEinZeichenOhneEcho();
		switch(*auswahl) {
			case '1':
				abbruch = sucheModellBezeichnung();
				// kann -1 zurückgeben: Suche abbrechen
				// kann 1 zurückgeben: Suche ausführen
				break;
			case '2':
				sucheKaelteLeistung(); abbruch = 1;
				break;
			case '3':
				sucheElektLeistung(); abbruch = 1;
				break;
			case '4':
				abbruch = sucheAbmessungen();
				// kann -1 zurückgeben: Suche abbrechen
				// kann 1 zurückgeben: Suche ausführen
				break;
			case '5':
				suchePreis(); abbruch = 1;
				break;
			case 0: case 'q': case 'Q': case 'x': case 'X': case 27:
				abbruch = -1;
				break;
		}
	} while(abbruch == 0);

	if (abbruch == 1) {
		// Ergebnis(se) anzeigen
		cls();
		printf("Suchergebnisse:\n");
		printf("\n");

		zeigeTabelle();

		printf("\n");
		warteAufTaste();

		filterAlleSichtbar(); // Filter wieder entfernen
	}
}

void tabellenMenu() {
	int n = nSichtbareGeraete();

	if (n < 1) {
		cls();
		printf("   (Es sind keine Geraete verfügbar...)\n");
		warteAufTaste();
		return;
	}

	do {
		cls();
		zeigeTabelle();

		int index = -1;
		if (n > 1) {
			index = datensatzWaehlenOderAbbruch("\nAktionen: <RETURN> zurück; Zahl: Details von # anzeigen\n:");
			if (index == -1) break;
		} else if (n == 1) {
			index = einzigesSichtbaresGeraet();
		}

		// okay, Detail-Ausgabe:
		cls();
		printf("Details von Gerät #%d:\n\n", index);
		ausgabeKlimageraet(&klimageraete[index]);
		printf("\n");
		warteAufTaste();
	} while (nSichtbareGeraete() > 1); // nur dann wiederholen, wenn es tatsächlich eine Auswahl gibt
}

void neuesGeraet() {
	cls();

	// freie Stelle suchen
	int index = getFreiesGeraet();
	if (index == -1) {
		printf("Es ist leider kein Speicherplatz mehr für neue Geräte vorhanden.\n\n");
		warteAufTaste();
		return;
	}

	// Meldung
	printf("Bitte geben sie die Daten des neuen Klimagerätes ein!\n\n");
	// eingeben
	eingabeKlimageraet(&klimageraete[index]);

	// Kontrollausgabe
	cls();
	printf("Danke - Ihr Gerät ist mit folgenden Daten als Datensatz #%d erfasst:\n\n", index);
	ausgabeKlimageraet(&klimageraete[index]);

	warteAufTaste();
}

void ersetzeGeraet() {
	cls();
	if (nGeraete() == 0) {
		printf("Es sind keine Geräte zum Ersetzen vorhanden.\n\n");
		warteAufTaste();
		return;
	}

	zeigeTabelle();
	int index=datensatzWaehlenOderAbbruch("\nWelches Gerät wollen Sie ersetzen? Bitte geben die die Nummer (#) ein:\n");
	if (index == -1) return; // undokumentiert: Abbruch

	// Meldung
	printf("Wir ersetzen den Eintrag #%d (%s).\n", index, klimageraete[index].modellBezeichnung);
	printf("Bitte geben sie die Daten des neuen Klimagerätes ein!\n\n");
	// eingeben
	eingabeKlimageraet(&klimageraete[index]);

	// Kontrollausgabe
	cls();
	printf("Danke - Ihr neues Gerät ist mit folgenden Daten als Datensatz #%d erfasst:\n\n", index);
	ausgabeKlimageraet(&klimageraete[index]);

	warteAufTaste();
}

void aendereGeraet() {
	cls();
	if (nGeraete() == 0) {
		printf("Es sind keine Geräte zum Ändern vorhanden.\n\n");
		warteAufTaste();
		return;
	}

	zeigeTabelle();
	int index=datensatzWaehlenOderAbbruch("\nWelches Gerät wollen Sie bearbeiten? Bitte geben die die Nummer (#) ein:\n");
	if (index == -1) return; // undokumentiert: Abbruch

	// Meldung
	cls();
	printf("Sie bearbeiten den Eintrag #%d (%s).\n", index, klimageraete[index].modellBezeichnung);
	// eingeben
	aendereKlimageraet(&klimageraete[index]);

	// Kontrollausgabe
	cls();
	printf("Das Gerät ist jetzt mit folgenden Daten erfasst:\n\n");
	ausgabeKlimageraet(&klimageraete[index]);

	warteAufTaste();
}

void loescheGeraet() {
	cls();
	if (nGeraete() == 0) {
		printf("Es sind keine Geräte zum Löschen vorhanden.\n\n");
		warteAufTaste();
		return;
	}

	zeigeTabelle();
	int index=datensatzWaehlenOderAbbruch("\nWelches Gerät wollen Sie löschen? Bitte geben die die Nummer (#) ein:\n");
	if (index == -1) return; // undokumentiert: Abbruch

	// Meldung
	cls();
	printf("Löschen von Eintrag #%d: \n", index);
	ausgabeKlimageraet(&klimageraete[index]);

	if (confirm("\nWollen Sie dieses Gerät wirklich löschen (j/n)? ") == 0)
		return; // Abbruch, nicht löschen

	// Kontrollausgabe
	cls();
	printf("Gerät #%d (%s) wurde gelöscht.\n\n", index, &klimageraete[index].modellBezeichnung[0]);

	// als frei markieren:
	klimageraete[index].modellBezeichnung[0] = '\0';

	warteAufTaste();
}


