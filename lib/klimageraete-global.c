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
 * gibt eine Meldung aus und wartet dann dementsprechend auf einen Tastendruck.
 */
void warteAufTaste() {
	printf("\nBitte drücken Sie zum Fortsetzen eine Taste. ");
	// globales "Flag" für die Eingabe: auch leere Eingabe akzeptieren:
	textEingabeAcceptEmpty = -1; // siehe lib/texteingabe.c
	// auf eine Taste warten, aber die Eingabe ignorieren / verwerfen:
	textEingabeEinZeichenOhneEcho();
}


float eingabePreis() {
	float retval = -1.0;
	// globales "Flag" für die Eingabe: keine leere Eingabe akzeptieren:
	textEingabeAcceptEmpty = 0; // siehe lib/texteingabe.c

	retval = (float)fliesskommaEingabe(9,2);
	while (retval<0) {
		printf("Der Preis muss größer als 0 sein.\n");
		retval = (float)fliesskommaEingabe(9,0);
	}

	return retval;
}

int eingabeIntGr0(const char * fehlermeldung) {
	int retval = -1;
	// globales "Flag" für die Eingabe: keine leere Eingabe akzeptieren:
	textEingabeAcceptEmpty = 0; // siehe lib/texteingabe.c

	retval = (int)fliesskommaEingabe(9,0);
	while (retval<=0) {
		printf("%s\n", fehlermeldung);
		retval = (int)fliesskommaEingabe(9,0);
	}

	return retval;
}
