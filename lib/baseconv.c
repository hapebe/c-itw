#include <stdio.h>
#include <stdlib.h>

/**
 * Bibliothek zur Umwandlung von Zahlen-Darstellung mit verschiedenen
 * Ziffern-Basen
 */

// did you know: eine unsigned long int-Zahl kann man mit printf so
// ausgeben:
// printf("%llu", 285212672);

// so lang darf eine symbolische Zahl maximal sein (die absolute Grenze
// ergibt sich dann aus dem Binärsystem --> 2^(MAX_LENGTH)-1)
#define MAX_LENGTH 64

// wenn 1, dann darf man "Buchstaben"-Ziffern groß und klein schreiben,
// sonst sollte der Wert 0 sein (und nur Zeichen in CHAR_POOL sind
// erlaubt)
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
 * Einfacher (long) int-Potenzrechner.
 * Gibt zurück: basis hoch exponent
 */
long int pow(long basis, int exponent) {
	long retval = 1;
	long prevRetval = retval;

	int i;
	for (i=0; i<exponent; i++) {
		prevRetval = retval;
		retval *= basis;

		if (prevRetval >= retval) {
			fprintf(stderr, "long int Overflow bei %lu ^ %d!\n", basis, exponent);
			exit(255);
		}
	}

	return retval;
}

/**
 * dekonstruiert die String-Darstellung einer Ganzzahl zu einer Basis
 * und gibt den Zahlenwert zurück
 */
long int getNumericIntBase(char * digits, long int basis) {
	if (!reverseCharPoolInitialized) {
		fprintf(stderr, "Es fehlt ein Aufruf von initReverseCharPool()! \n");
	}

	int i;
	int negative = 0;

	// Wie lang ist die Zahl? (0-terminierter String...)
	int length = 0;
	while ((digits[length] != 0) && (length < MAX_LENGTH)) length++;
		// printf("Die symbolische Zahl %s ist %d Stellen lang.\n", digits, length);

	long int retval = 0;
	long int prevRetval = 0;
	for (i=0; i<length; i++) {
		char symbol = digits[i];
		if (symbol == '-') {
			negative = -1;
			continue;
		}

		long int stellenwert = pow(basis, (length-i-1));
			// printf("Der Stellenwert an %d ist %lu.\n", i, stellenwert);

		int ziffernwert = reverseCharPool[(int)symbol];
		// Fehlerbehandlung:
		if (ziffernwert >= basis) {
			fprintf(stderr, "Die Ziffer '%c' ist im Zahlensystem zur Basis %lu nicht erlaubt!\n", symbol, basis);
			ziffernwert = 0;
		}

		prevRetval = retval;
		retval += ziffernwert*stellenwert;
			// printf("Summiere: %lu\n", retval);
		if (prevRetval > retval) {
			fprintf(stderr, "long int Overflow nach %d Stellen von %s!\n", i+1, digits);
			exit(255);
		}
	}

		// printf("retval vor dem ggf. Negieren: %ld\n", retval);
	if (negative) retval *= -1;
		// printf("retval nach dem ggf. Negieren: %ld\n", retval);
	return retval;
}



/**
 * wandelt z in eine String-Repräsentation im Zahlensystem zur Basis
 * basis um
 */
char* getSymbolicIntBase(long int z, int basis) {

	char digits[MAX_LENGTH];
	static char retval[MAX_LENGTH];

	long int remainder = z;
	if (z < 0) remainder = -z;

	int cursor = 0;
	long int modulo = 0;
	while (remainder > 0) {
		modulo = remainder % basis;
		digits[cursor] = modulo;
		cursor ++;

		remainder /= basis;
	}
	int numDigits = cursor;

	// Zahl ausgeben:
	cursor = 0;
	if (z < 0) { retval[cursor] = '-'; cursor ++; }

	int i;
	for (i=numDigits-1; i>=0; i--) { // von hinten nach vorne...
		retval[cursor] = CHAR_POOL[ (int)digits[i] ];
		cursor ++;
	}

	if (cursor == 0) {
		// wir haben keine Zeichen - die Zahl war wohl 0:
		retval[cursor] = CHAR_POOL[0];
		cursor ++;
	}

	// ans Ende \0, um den String zu terminieren:
	retval[cursor] = 0;

	return &retval[0];
}
