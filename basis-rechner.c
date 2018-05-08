#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#endif
#ifdef __linux__
#include "lib/getch.c"
#endif

#include "lib/baseconv.c"

/**
 * Dieses Programm kann Zahlen von und in verschiedene Zahlensysteme
 * (verschiedene Basen) umwandeln.
 *
 * Zentral sind die Funktionen (in lib/baseconv.c):
 *
 * int getNumericIntBase(char * digits, int basis)
 *    (wandelt eine symbolische Zahl in einen int um)
 *
 * char* getSymbolicIntBase(int z, int basis)
 *    (wandelt einen int in eine symbolische Zahl um)
 *
 */



/**
 * dekonstruiert (und gibt direkt auf stdout aus) die String-Darstellung
 * einer Zahl zu einer Basis
 */
void explainIntBase(char * digits, int basis) {
	if (!reverseCharPoolInitialized) {
		fprintf(stderr, "Es fehlt ein Aufruf von initReverseCharPool()! \n");
	}

	int i;

	// das ist hier etwas holprig, aber im Moment weiß ich nichts besseres:
	char digitsArray[MAX_LENGTH];
	for (i=0; i<MAX_LENGTH; i++) {
		digitsArray[i] = *digits;
		digits += 1; // Pointer um ein "Element" weiterschieben
	}
	// printf("Eingabe: %s\n", digitsArray);

	// Wie lang ist die Zahl?
	int length = 0;
	while ((digitsArray[length] != 0) && (length < MAX_LENGTH)) length++;

	int sum = 0;
	for (i=0; i<length; i++) {
		if (i==0) printf("  "); else printf("+ ");

		int stellenwert = pow(basis, (length-i-1));
		char symbol = digitsArray[i];
		int ziffernwert = reverseCharPool[(int)symbol];
		// Fehlerbehandlung:
		if (ziffernwert >= basis) {
			fprintf(stderr, "Die Ziffer '%c' ist im Zahlensystem zur Basis %d nicht erlaubt!\n", symbol, basis);
			ziffernwert = 0;
		}

		printf("%2d * %6d = %7d\n", ziffernwert, stellenwert, ziffernwert*stellenwert);

		sum += ziffernwert*stellenwert;
	}
	printf("-----------------------\n");
	printf("              = %7d\n", sum);
}





/**
 * liest zeichenweise eine symbolische Zahl zur Basis basis ein.
 * buffer muss dabei auf ein char-Array zeigen, dass das Ergebnis
 * aufnehmen kann
 *
 * TODO: Auch mit Backspace umgehen (siehe lib/texteingabe.c)...
 */
void readFromConsole(char* buffer, int basis) {
	int i = 0;
	int fertig = 0;

	while ((i<MAX_LENGTH-1) && (!fertig)) {
		char c;
		int okay;
		do {
			okay = -1; // optimistisch!
			c = getch();
			if (c > 127) okay = 0;

			if (c == 10 || c == 13) {
				// Eingabe / Enter / Return
				okay = false;
				if (i > 0) {
					// wir wollen mindestens eine Ziffer - also Return
					// am Anfang ignorieren
					fertig = -1;
					break;
				}
			}

			int wert = reverseCharPool[(int)c];
			if (wert >= basis) okay = 0;
		} while (!okay);

		if (okay) {
			printf("%c", c);
			buffer[i] = c;
			i++;
		}
	}
	buffer[i] = '\0'; // 0-terminierter String als Ergebnis
}



int main(void) {
	initReverseCharPool();

	int z, basis;
	char eingabe[MAX_LENGTH];

	// in diesen Basen wird die eingegebene Zahl später angezeigt:
	int basen[] = {2, 3, 4, 5, 8, 10, 16, 36};

	printf("Mit welcher Zahlensystem-Basis wollen Sie Ihre Zahl eingeben (2..36): ");
	scanf("%d", &basis);
	fflush(stdin);
	if (basis < 2 || basis > 36) {
		fprintf(stderr, "Die Basis liegt nicht zwischen 2 und 36 (inklusiv)!");
		return 1;
	}

	printf("Bitte geben Sie eine entsprechende Ganzzahl ein: ");
	// scanf("%s", &eingabe[0]);
	readFromConsole(&eingabe[0], basis); printf("\n");

	z = getNumericIntBase(eingabe, basis); // in int-Zahl umwandeln
	printf("Ihre symbolische Zahl bedeutet im %der-System:\n", basis);
	explainIntBase(eingabe, basis);
	printf("\n");

	printf("Hier kommt Ihre Zahl in fremden Basen: \n");
	int i;
	for (i=0; i<8; i++) {
		basis = basen[i];
		char* bunteZahl = getSymbolicIntBase(z, basis);
		printf("%s(Basis %d)\n", bunteZahl, basis);
		explainIntBase(bunteZahl, basis);
		printf("\n");
	}

	return 0;
}
