#define DEBUG -1

#include "lib/klimageraete-global.c"
#include "lib/klimageraete-core.c" // alles, was direkt die Verarbeitung des Typs "t_klimageraet" betrifft
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
	int i=0;
	for (i=0; i<MAX_GERAETE; i++) {
		klimageraete[i].modellBezeichnung[0] = '\0';
		filterKlimageraete[i] = FILTER_SICHTBAR;
	}

	// TODO: nach Tests raus:
#ifdef DEBUG
	initTest();
#endif

	// TODO: wenn Datenbank auf der Festplatte existiert, diese gleich
	// wieder einlesen
}

void destroy() {
	// TODO: wenn Datensätze existieren, diese als Datei sichern.
	// Sonst möglicherweise bestehende Datei löschen.
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
	if (nGeraete() <= 0) {
		printf("   (Es sind keine Geraete verfügbar...)\n");
		return;
	}
	if (nSichtbareGeraete() <= 0) {
		printf("   (Es gibt keine Suchergebnisse...)\n");
		return;
	}

	int i;
	if (nSichtbareGeraete() == 1) {
		// Sonderfall: direkt die Details anzeigen
		for (i=0; i<MAX_GERAETE; i++) {
			if (istFreiesGeraet(&klimageraete[i])) continue;
			if (filterKlimageraete[i] == FILTER_VERSTECKT) continue;
			ausgabeKlimageraet(&klimageraete[i]);
			return;
		}
	}

	printf("   # ");
	printKlimageraetZeilenUeberschrift();
	printf("     ");
	printKlimageraetZeilenUntertitel();
	printf("====|");
	printKlimageraetZeilenSeparator();

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
				break;
			case '2':
				sucheKaelteLeistung(); abbruch = 1;
				break;
			case '3':
				sucheElektLeistung(); abbruch = 1;
				break;
			case '4':
				abbruch = sucheAbmessungen();
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
	while(-1) {
		cls();
		zeigeTabelle();

		printf("\nAktionen: <RETURN> zurück; #Zahl: Details anzeigen\n:");
		int index = datensatzWaehlenOderAbbruch();
		if (index == -1) break;

		// okay, Detail-Ausgabe:
		cls();
		printf("Details von Gerät #%d:\n\n", index);
		ausgabeKlimageraet(&klimageraete[index]);
		printf("\n");
		warteAufTaste();
	}
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

	zeigeTabelle();
	printf("\nWelches Gerät wollen Sie ersetzen? Bitte geben die die Nummer (#) ein:\n");
	int index=datensatzWaehlenOderAbbruch();

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

	zeigeTabelle();
	printf("\nWelches Gerät wollen Sie bearbeiten? Bitte geben die die Nummer (#) ein:\n");
	int index=datensatzWaehlenOderAbbruch();

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

	zeigeTabelle();
	printf("\nWelches Gerät wollen Sie löschen? Bitte geben die die Nummer (#) ein:\n");
	int index=datensatzWaehlenOderAbbruch();

	if (index == -1) return; // undokumentiert: Abbruch

	// Meldung
	cls();
	printf("Löschen von Eintrag #%d: \n", index);
	ausgabeKlimageraet(&klimageraete[index]);
	printf("\nWollen Sie dieses Gerät wirklich löschen (j/n)? ");
	textEingabeAcceptEmpty = 0;
	char * auswahl = texteingabeLengthSet(1, (char[]){'j','J','y','Y','n','N'});

	if (*auswahl == 'n' || *auswahl == 'N')	return; // Abbruch, nicht löschen

	// Kontrollausgabe
	cls();
	printf("Gerät #%d (%s) wurde gelöscht.\n\n", index, &klimageraete[index].modellBezeichnung[0]);

	// als frei markieren:
	klimageraete[index].modellBezeichnung[0] = '\0';

	warteAufTaste();
}


