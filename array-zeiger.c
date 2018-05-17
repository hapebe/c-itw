#include <stdio.h>
#include "lib/texteingabe.c"

#define ANZAHL 10

void intInArrayEingeben(int*, int);

int main(int argc, char** argv) {
	int zahlen[ANZAHL];

	intInArrayEingeben(&zahlen[0], ANZAHL);
	printf("Danke für Ihre Eingabe. Die Zahlen sind:\n");

	int i;
	for (i=0; i<ANZAHL; i++) {
		printf("[%d.] %d\n", (i+1), zahlen[i]);
	}
}

void intInArrayEingeben(int* zahlen, int anzahl) {
	// globales "Flag" für die Eingabe: keine leeren Eingabe akzeptieren:
	textEingabeAcceptEmpty = 0; // siehe lib/texteingabe.c

	int i;
	for (i=0; i<anzahl; i++) {
		printf("Bitte geben Sie die %d. Zahl ein:\n",i+1);

		// Variante, den Zeiger direkt als Array zu behandeln:
		// zahlen[i] = (int)fliesskommaEingabe(16,0);

		// Variante, den Zeiger zu inkrementieren und zu dereferenzieren:
		*(zahlen+i) =  (int)fliesskommaEingabe(16,0); // aus lib/texteingabe.c
	}
}
