#include <stdio.h>
#include "../lib/texteingabe.c"

#define MIN_PW_LEN 10

/**
 * globaler Zustand
 */
char passwort[60];
char filename[256];

// forward declarations:
void init(void);
void destroy(void);

void hauptMenu(void);
void setzeDateiname(void);
void setzePasswort(void);
void verschluesseln(void);
void entschluesseln(void);
int pruefeDateiUndPW(void);
char * dateiNameOhneErweiterung(const char * vollerName);

void cls(void);
int file_exists(const char *);


int main(int argc, char** argv) {
	init(); // definierten Start-Zustand herstellen

	hauptMenu();

	destroy(); // End-Zustand definiert behandeln
	return 0;
}

void hauptMenu() {
	int abbruch = 0;
	do {
		cls();

		printf("Hauptmenü\n");
		printf("\n");
		if (strlen(filename) > 0) {
			printf("  Aktueller Dateiname: %s\n", filename);
		}
		if (strlen(passwort) > 0) {
			printf("  Passwort ist vorhanden.\n");
		}
		printf("\n");
		printf("\t1\tDateinamen wählen\n");
		printf("\t2\tPasswort wählen\n");
		printf("\t3\tDatei verschlüsseln\n");
		printf("\t4\tDatei entschlüsseln\n");
		printf("\n");
		printf("\tx\tBeenden\n");

		fflush(stdin);
		char * auswahl = textEingabeEinZeichenOhneEcho();
		switch(*auswahl) {
			case '1':
				setzeDateiname(); break;
			case '2':
				setzePasswort(); break;
			case '3':
				verschluesseln(); break;
			case '4':
				entschluesseln(); break;
			case 'q': case 'Q': case 'x': case 'X': case 27: case 0:
				abbruch = -1;
				break;
		}
	} while(!abbruch);
}

void setzeDateiname() {
	char * tempName;

	cls();
	printf("Bitte geben Sie den Dateinamen mit den zu ver- oder entschlüsselnden Daten ein:\n");
	textEingabeAcceptEmpty = -1;
	do {
		tempName = texteingabeLength(255);
		if (strlen(tempName) == 0) return; // Abbruch!

		if (!file_exists(tempName)) {
			printf("Auf '%s' kann nicht zugegriffen werden. Bitte geben Sie einen anderen Dateinamen ein, oder nichts, um abzubrechen!\n", tempName);
		}
	} while(!file_exists(tempName));

	// globale Variable setzen:
	strcpy(filename, tempName);
}

void setzePasswort() {
	char * temp;

	cls();
	printf("Bitte geben Sie das Passwort / den Schlüssel ein:\n");
	printf("(Leer für Abbruch)\n");
	textEingabeAcceptEmpty = -1;

	do {
		temp = texteingabeLength(59);
		if (strlen(temp) == 0) return; // Abbruch!

		if (strlen(temp) < MIN_PW_LEN) {
			printf("Tut mir leid, aber das Passwort muss mindestens %d Zeichen haben. Bitte geben Sie ein längeres ein, oder nicht, um abzubrechen!\n", MIN_PW_LEN);
		}
	} while (strlen(temp) < MIN_PW_LEN);


	// globale Variable setzen:
	strcpy(passwort, temp);
}

void verschluesseln() {
	cls();
	if (!pruefeDateiUndPW()) {
		warteAufTaste();
		return;
	}

	int lPW = strlen(passwort);

	char outFilename[256];
	char * pOutFilename = &outFilename[0];
	strcpy(pOutFilename, dateiNameOhneErweiterung(filename));
	strcat(pOutFilename, ".ver");
	// printf("%s", pOutFilename); warteAufTaste(); // debug-Ausgabe

	// Ein- und Ausgabedatei öffnen - ggf. Fehler melden
	FILE * in, * out;
	if ( !(in = fopen(filename, "r")) ) {
		fprintf(stderr, "Kann die Eingabedatei '%s' nicht lesen.\n", filename);
		return;
	}
	if ( !(out = fopen(pOutFilename, "w")) ) {
		fprintf(stderr, "Kann nicht in die Ausgabedatei '%s' schreiben.\n", pOutFilename);
		return;
	}

	// Zeichenweises kopieren mit zwischengeschobener Verknüpfung
	char temp;
	int cnt = 0;
	while ( EOF != (temp = fgetc(in)) ) {
		temp += passwort[cnt % lPW];
		fputc(temp, out);
		cnt ++;
	}

	// Dateien schließen
	fclose(in);
	fclose(out);

	// Meldung
	printf("Die verschlüsselte Datei '%s' wurde erstellt.\n\n", pOutFilename);
	warteAufTaste();
}

void entschluesseln() {
	cls();
	if (!pruefeDateiUndPW()) {
		warteAufTaste();
		return;
	}

	int lPW = strlen(passwort);

	// Eingabedatei öffnen - ggf. Fehler melden (Ausgabedatei ist die Konsole / stdout ...)
	FILE * in;
	if ( !(in = fopen(filename, "r")) ) {
		fprintf(stderr, "Kann die Eingabedatei '%s' nicht lesen.\n", filename);
		return;
	}

	printf("Die entschlüsselten Daten stehen zwischen den Linien:\n\n");
	printf("------------------------------------------------------------\n");

	// Zeichenweises Ausgeben mit vorheriger Verknüpfung
	char temp;
	int cnt = 0;
	while ( EOF != (temp = fgetc(in)) ) {
		temp -= passwort[cnt % lPW];
		fputc(temp, stdout);
		cnt ++;
	}

	// Datei schließen
	fclose(in);

	printf("------------------------------------------------------------\n");
	printf("\n");
	warteAufTaste();
}

/**
 * @return -1, wenn alles okay ist; 0, wenn es Probleme gibt
 */
int pruefeDateiUndPW() {
	int fehler = 0;
	if (strlen(filename) == 0) {
		fprintf(stderr, "Es ist kein Dateiname vorhanden.\n");
		fehler = -1;
	} else if (!file_exists(filename)) {
		printf("Auf '%s' kann nicht zugegriffen werden.\n", filename);
		fehler = -1;
	}
	if (strlen(passwort) == 0) {
		fprintf(stderr, "Es ist kein Passwort vorhanden.\n");
		fehler = -1;
	} else if (strlen(passwort) < MIN_PW_LEN) {
		// das sollte gar nicht passieren, weil schon bei der Eingabe überprüft, aber wer weiß...
		fprintf(stderr, "Das Passwort ist zu kurz.\n");
		fehler = -1;
	}

	if (fehler) return 0;
	return -1;
}

/**
 * löscht den Konsolen-Bildschirm
 * (tricky wegen Unterschieden Windows/Linux)
 */
void cls() {
#ifdef _WIN32
	system("cls");
#endif

#ifdef __linux__
	system("clear");
#endif
}

/**
 * Source: http://www.zentut.com/c-tutorial/c-file-exists/
 * Check if a file exist using fopen() function
 * @return 1 if the file exist otherwise return 0
 */
int file_exists(const char * filename) {
    /* try to open file to read */
    FILE *file;
    if ((file = (fopen(filename, "r")))) {
        fclose(file);
        return 1;
    }
    return 0;
}


char * dateiNameOhneErweiterung(const char * vollerName) {
	static char puffer[256];
	static char * pPuffer = &puffer[0];

	if (strlen(vollerName) > 255) {
		// TODO: Fehlerbehandlung
		return NULL;
	}

	// dann jedenfalls in den Zielpuffer kopieren:
	strcpy(pPuffer, vollerName);

	// suche das letzte Vorkommen eines Punktes im vollen Namen:
	int i, fundStelle = -1;
	for (i=strlen(vollerName)-1; i>=0; i--) {
		if (vollerName[i] == '.') {
			fundStelle = i;
			break;
		}
	}
	// letzten Punkt mit dem Null-Byte ersetzen - komplette Endung entfernen:
	if (fundStelle >= 0) {
		puffer[fundStelle] = '\0';
	}

	return pPuffer;
}


void init() {
	// Dateinamen und Passwort garantiert zu leeren Strings machen:
	filename[0] = '\0';
	passwort[0] = '\0';
}

void destroy() {
}

