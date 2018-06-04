#include <stdio.h>

#define die(TEXT) do {printf ("\n\n%s:%d:%s\n", __FILE__, __LINE__, TEXT); exit(255);} while (0);

#include <stdlib.h> // für atoi() / itoa() / exit()
#include <ctype.h> // für isspace()
#include <string.h>
#ifdef DEBUG
	#include "./dump.c"
#endif
#include "./string-utils.c"
#include "./texteingabe.c"

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
 * @return -1 wenn bestätigt, 0 wenn nicht
 */
int confirm(char * message) {
	printf("%s", message);
	textEingabeAcceptEmpty = 0;
	char * auswahl = texteingabeLengthSet(1, (char[]){'j','J','y','Y','n','N'});

	if (*auswahl == 'n' || *auswahl == 'N')	return 0; // nicht bestätigt

	return -1; // ja/yes
}

float eingabePreis() {
	float retval = -1.0;
	// globales "Flag" für die Eingabe: keine leere Eingabe akzeptieren:
	textEingabeAcceptEmpty = 0; // siehe lib/texteingabe.c

	while (retval<0) {
		retval = (float)fliesskommaEingabe(6,2);
		if (retval<0) {
			printf("Der Preis darf nicht kleiner als 0 sein.\n");
		}
	}

	return retval;
}

float eingabePreisOderLeer() {
	float retval = -1.0;
	// globales "Flag" für die Eingabe: keine leere Eingabe akzeptieren:
	textEingabeAcceptEmpty = -1; // siehe lib/texteingabe.c

	while (retval<0) {
		retval = (float)fliesskommaEingabe(6,2);
		if (flagLeereEingabe) return 0.0; // siehe lib/texteingabe.c - wird gesetzt, wenn nichts eingegeben wurde

		if (retval<0) {
			printf("Der Preis darf nicht kleiner als 0 sein.\n");
		}
	}

	return retval;
}


int eingabeIntGr0(const char * fehlermeldung) {
	int retval = -1;
	// globales "Flag" für die Eingabe: keine leere Eingabe akzeptieren:
	textEingabeAcceptEmpty = 0; // siehe lib/texteingabe.c

	while (retval<=0) {
		retval = (int)fliesskommaEingabe(9,0);
		if (retval <=0) {
			printf("%s\n", fehlermeldung);
		}
	}

	return retval;
}

/**
 * @return eingegebene Zahl (größer als 0), oder -1 für leere Eingabe
 */
int eingabeIntGr0OderLeer(const char * fehlermeldung) {
	char * ptrPuffer;

	int retval = -1;
	// globales "Flag" für die Eingabe: leere Eingabe akzeptieren:
	textEingabeAcceptEmpty = -1; // siehe lib/texteingabe.c

	while (retval<=0) {
		ptrPuffer = texteingabeLengthSet(9, DEZIMAL_ZIFFERN);
		if (strlen(ptrPuffer) == 0) return -1; // leere Eingabe: -1 zurückgeben
		retval = atoi(ptrPuffer);

		if (retval <=0) {
			printf("%s\n", fehlermeldung);
		}
	}

	return retval;
}

