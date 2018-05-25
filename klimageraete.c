#define DEBUG -1

#include "lib/klimageraete-global.c"
#include "lib/klimageraete-core.c" // alles, was direkt die Verarbeitung des Typs "t_klimageraet" betrifft
#include "lib/klimageraete-suche.c"
#ifdef DEBUG
	#include "lib/klimageraete-test.c" // für initTest(...);
#endif

void init(void);
void zeigeHauptMenu(void); // nur Anzeige
void tabellenMenu(void); // Anzeige und Verarbeitung
void suchMenu(void); // Anzeige und Verarbeitung
void zeigeTabelle(void);
void debugPrintStatus(void);
void neuesGeraet(); // interaktive Prozedur: neuen Datensatz anlegen
void ersetzeGeraet(); // interaktive Prozedur: Datensatz ersetzen
int datensatzWaehlenOderAbbruch(void); // Eingabe-Funktion
int nGeraete(void);
int nSichtbareGeraete(void);
int getFreiesGeraet(void);

int main(int argc, char** argv) {
	init(); // definierten Start-Zustand herstellen
	// debugPrintStatus();

	int abbruch = 0;
	do {
		zeigeHauptMenu();
		char * auswahl = textEingabeEinZeichenOhneEcho();
		switch(*auswahl) {
			case '1': // eingeben
				neuesGeraet();
				break;
			case '2': // ausgeben
				tabellenMenu();
				break;
			case '3': // ersetzen
				ersetzeGeraet();
				break;
			case '4': // suchen
				suchMenu();
				break;
			case '5': case 'q': case 'Q': case 'x': case 'X': case 27:
				abbruch = -1;
				break;
		}
	} while(!abbruch);

	return 0;
}

void init() {
	int i=0;
	for (i=0; i<MAX_GERAETE; i++) {
		statusKlimageraete[i] = FREI;
		filterKlimageraete[i] = FILTER_SICHTBAR;
	}

	// TODO: nach Tests raus:
#ifdef DEBUG
	initTest();
#endif

	// TODO: wenn Datenbank auf der Festplatte existiert, diese gleich
	// wieder einlesen
}

void zeigeHauptMenu() {
	cls();

	printf("Hauptmenü\n");
	printf("\n");
	printf("* Es befinden sich aktuell %d Klimageräte in der Datenbank. *\n", nGeraete());
	printf("\n");
	printf("\t1\tEingabe\n");
	printf("\t2\tAusgabe\n");
	printf("\t3\tErsetzen\n");
	printf("\t4\tSuchen\n");
	printf("\t5\tBeenden\n");
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
			if (statusKlimageraete[i] == FREI) continue;
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
		if (statusKlimageraete[i] == FREI) continue;
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
				sucheModellBezeichnung(); abbruch = 1;
				break;
			case '2':
				sucheKaelteLeistung(); abbruch = 1;
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

/**
 * ermöglicht die Auswahl einer gültigen Datensatznummer, oder Abbruch bei leerer Eingabe:
 * @return gültiger Index von klimageraete[] oder -1 für Abbruch
 */
int datensatzWaehlenOderAbbruch(void) {
	static char buffer[32];
	char * ptrBuffer = &buffer[0];

	do {
		fgets(ptrBuffer, 31, stdin);
		// dump(trim(ptrBuffer)); warteAufTaste(); // DEBUG

		if (strlen(trim(ptrBuffer)) == 0) return -1; // Schleife und Funktion verlassen

		int index = atoi(trim(ptrBuffer));
		if (index < 0 || index >= MAX_GERAETE) {
			printf("%d ist keine gültige Geräte-Nummer.\n", index);
		} else if (statusKlimageraete[index] == FREI) {
			printf("Nummer %d enthält keinen Datensatz.\n", index);
		} else {
			return index;
		}
	} while(-1); // wird per return verlassen
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
	statusKlimageraete[index] = BELEGT;

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


void debugPrintStatus() {
	int i;
	printf("status:\n");
	for (i=0; i<MAX_GERAETE; i++) {
		printf("%d ", statusKlimageraete[i]);
		if ((i+1) % 10 == 0) printf("\n");
	}
	printf("\n");
	printf("filter:\n");
	for (i=0; i<MAX_GERAETE; i++) {
		printf("%d ", filterKlimageraete[i]);
		if ((i+1) % 10 == 0) printf("\n");
	}
	printf("\n");
}

/**
 * gibt die Anzahl vorhandener Klimageräte zurück
 */
int nGeraete(void) {
	int n = 0;

	int i;
	for (i=0; i<MAX_GERAETE; i++) {
		if (statusKlimageraete[i] == BELEGT) n++;
	}
	return n;
}

/**
 * gibt die Anzahl sichtbarer Klimageräte zurück
 */
int nSichtbareGeraete(void) {
	int n = 0;

	int i;
	for (i=0; i<MAX_GERAETE; i++) {
		if (statusKlimageraete[i] == BELEGT && filterKlimageraete[i] == FILTER_SICHTBAR) n++;
	}
	return n;
}

/**
 * @return index eines freien Datensatzes in klimageraete[] oder -1, wenn es keine freien Plätze gibt.
 */
int getFreiesGeraet(void) {
	int i;
	for (i=0; i<MAX_GERAETE; i++) {
		if (statusKlimageraete[i] == FREI) return i;
	}
	return -1;
}
