#include <stdio.h>
#include "lib/texteingabe.c"

#define MAX 5
#define MAX_INPUT_LENGTH 9

void cls();
void menuZeigen();
void arrayEingeben(int*, int);
void arrayAusgeben(int*, int);

// globale Variable als Speicher für die zu verarbeitenden Zahlen
int zahlen[MAX];

int main(int argc, char** argv) {
	int beenden = 0;
	while (!beenden) {
		// Menü zeigen und Aktion erfragen:
		menuZeigen();
		char c = *textEingabeEinZeichenOhneEcho(); // aus lib/texteingabe.c
		printf("%c\n", c); // Ausgabe ist eigentlich unnötig
		// bereit für den nächsten Schritt:
		cls();

		// Aktion ausführen:
		switch(c) {
			case '1':
				arrayEingeben(&zahlen[0], MAX);
				break;
			case '2':
				arrayAusgeben(&zahlen[0], MAX);
				printf("\nBitte drücken Sie zum Fortsetzen eine Taste. ");
				// globales "Flag" für die Eingabe: auch leere Eingabe akzeptieren:
				textEingabeAcceptEmpty = -1; // siehe lib/texteingabe.c
				// auf eine Taste warten, aber die Eingabe ignorieren / verwerfen:
				textEingabeEinZeichenOhneEcho();
				break;
			case 'q': case 'Q':
			case 'x': case 'X':
			case 27: /*ESC*/
				beenden = -1; // Flag signalisiert: Abbruch der Hauptschleife
				break;
		}
	}

	return 0;
}

void menuZeigen() {
	cls();
	printf("\n");
	printf("\t1\tZahlen eingeben\n");
	printf("\t2\tZahlen ausgeben\n");
	printf("\tq\tBeenden\n");
	printf("\n");
	printf("\tBitte wählen Sie: ");

}

/**
 * @param pArray Zeiger auf ein int-Array
 * @param n Anzahl Elemente in diesem Array
 */
void arrayEingeben(int* pArray, int n) {
	// globales "Flag" für die Eingabe: keine leeren Eingabe akzeptieren:
	textEingabeAcceptEmpty = 0; // siehe lib/texteingabe.c

	printf("Bitte geben Sie %d Zahlen ein!\n\n", n);

	int i;
	for (i=0; i<n; i++) {
		printf("Bitte geben Sie die %d. Zahl ein:\n",i+1);
		*(pArray+i) =  (int)fliesskommaEingabe(MAX_INPUT_LENGTH,0); // aus lib/texteingabe.c
	}
}

/**
 * @param pArray Zeiger auf ein int-Array
 * @param n Anzahl Elemente in diesem Array
 */
void arrayAusgeben(int* pArray, int n) {
	printf("Die Reihe mit %d Zahlen enthält:\n\n", n);

	int i;
	for (i=0; i<n; i++) {
		printf("[%3d]\t%d\n", i, *(pArray+i));
	}
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

