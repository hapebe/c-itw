#include <stdio.h>

/**
 * Bibliothek zur Umwandlung von Zahlen-Darstellung mit verschiedenen
 * Ziffern-Basen
 */

// so lang darf eine symbolische Zahl maximal sein (die absolute Grenze
// ergibt sich dann aus dem Binärsystem --> 2^(MAX_LENGTH-1)-1)
#define MAX_LENGTH 32

// wenn 1, dann darf man "Buchstaben"-Ziffern groß und klein schreiben
// sonst sollte der Wert 0 sein
#define ALLOW_MIXED_CASE 1

// das sind die Ziffern-Zeichen-Konstanten für alle Basen:
const char CHAR_POOL[] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'L', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z'
};

// das hier wird programmatisch initilisiert, so dass es eine
// Reverse-Lookup-Tabelle der vorstehenden Symbole auf ihre
// Ziffernwerte enthält.
char reverseCharPool[128];
// flag: wenn nicht initialisert, gibt es eine Fehlermeldung
int reverseCharPoolInitialized = 0;

/*
 * füllt eine Look-Up-Tabelle mit den numerischen Werten der Ziffern-Zeichen
 */
void initReverseCharPool() {
	int i;
	for (i=0; i<128; i++) reverseCharPool[i] = -1; // als Marker für "ungültig"

	for (i=0; i<36; i++) {
		char symbol = CHAR_POOL[i];

		if (ALLOW_MIXED_CASE && (symbol & 0x40)) { // Buchstaben sind alle in der zweiten ASCII-Code-Hälfte > 64...
			char symbolUpper = symbol & 0x5f;
			reverseCharPool[(int)symbolUpper] = i;

			char symbolLower = symbol | 0x20;
			reverseCharPool[(int)symbolLower] = i;
		} else {
			reverseCharPool[(int)symbol] = i;
		}
	}
	reverseCharPoolInitialized = -1;

	// Debug-Ausgabe: Wie sieht diese Tabelle denn jetzt aus?
	/*
	printf("reverseCharPool[] = \n");
	for (i=0; i<128; i++) {
		char v = reverseCharPool[i];
		if (v != -1) {
			printf("%3d", reverseCharPool[i]);
		} else {
			printf("  .");
		}
		if ((i+1) % 16 == 0) printf("\n");
	}
	printf("\n");
	*/
}



/**
 * Einfacher int-Potenzrechner.
 * Gibt zurück: basis hoch exponent
 */
int pow(int basis, int exponent) {
	int retval = 1;

	int i;
	for (i=0; i<exponent; i++) retval *= basis;

	return retval;
}

/**
 * dekonstruiert die String-Darstellung einer Ganzzahl zu einer Basis
 * und gibt den Zahlenwert zurück
 */
int getNumericIntBase(char * digits, int basis) {
	if (!reverseCharPoolInitialized) {
		fprintf(stderr, "Es fehlt ein Aufruf von initReverseCharPool()! \n");
	}

	int i;
	int negative = 0;

	// Parameter als char[] verfügbar machen -
	// das ist hier etwas holprig, aber im Moment weiß ich nichts besseres:
	char digitsArray[MAX_LENGTH];
	for (i=0; i<MAX_LENGTH; i++) {
		digitsArray[i] = *digits;
		digits += 1; // Pointer um ein "Element" weiterschieben
	}

	// Wie lang ist die Zahl? (0-terminierter String...)
	int length = 0;
	while ((digitsArray[length] != 0) && (length < MAX_LENGTH)) length++;

	int retval = 0;
	for (i=0; i<length; i++) {
		int stellenwert = pow(basis, (length-i-1));

		char symbol = digitsArray[i];
		if (symbol == '-') {
			negative = -1;
			continue;
		}

		int ziffernwert = reverseCharPool[(int)symbol];
		// Fehlerbehandlung:
		if (ziffernwert >= basis) {
			fprintf(stderr, "Die Ziffer '%c' ist im Zahlensystem zur Basis %d nicht erlaubt!\n", symbol, basis);
			ziffernwert = 0;
		}

		retval += ziffernwert*stellenwert;
	}

	if (negative) retval *= -1;
	return retval;
}



/**
 * wandelt z in eine String-Repräsentation im Zahlensystem zur Basis
 * basis um
 */
char* getSymbolicIntBase(int z, int basis) {

	char digits[MAX_LENGTH];
	static char retval[MAX_LENGTH];

	int remainder = z;
	if (z < 0) remainder = -z;

	int cursor = 0, modulo = 0;
	while (remainder > 0) {
		modulo = remainder % basis;
		digits[cursor] = modulo;
		cursor ++;

		remainder /= basis;
	}

	// Zahl ausgeben:
	if (z < 0) printf("-");
	int i;
	int writePos = 0;
	retval[cursor] = 0; // \0, um den String zu terminieren
	for (i=cursor-1; i>=0; i--) {
		retval[writePos] = CHAR_POOL[ (int)digits[i] ];
		writePos ++;
	}

	return &retval[0];
}
