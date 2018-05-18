#include <stdio.h>
#include "lib/texteingabe.c"

#define MAX 5
#define MAX_INPUT_LENGTH 9

// Modus-Konstanten für die Funktion
#define STATISTIK_MIN 1
#define STATISTIK_MAX 2

void cls();
void warteAufTaste();
void menuZeigen();
void arrayEingeben(int*, int);
void zahlAendern(int*, int);
void arraySortieren(int*, int);
void arrayAusgeben(int*, int);
void statistikAusgeben(int*, int, int);

// globale Variable als Speicher für die zu verarbeitenden Zahlen
int zahlen[MAX];

int main(int argc, char** argv) {
	int i;

	// am Anfang Eingabe von Zahlen "erzwingen":
	arrayEingeben(&zahlen[0], MAX);

	int beenden = 0;
	while (!beenden) {
		// Menü zeigen und Aktion erfragen:
		menuZeigen();
		char c = *textEingabeEinZeichenOhneEcho(); // aus lib/texteingabe.c
		// printf("%c\n", c); // Ausgabe ist eigentlich unnötig
		cls();

		// Aktion ausführen:
		switch(c) {
			case '1':
				arrayEingeben(&zahlen[0], MAX);
				break;
			case '2':
				printf("Inhalte der Zahlen-Liste:\n\n");
				arrayAusgeben(&zahlen[0], MAX);
				warteAufTaste();
				break;
			case '3':
				statistikAusgeben(&zahlen[0], MAX, STATISTIK_MIN);
				warteAufTaste();
				break;
			case '4':
				statistikAusgeben(&zahlen[0], MAX, STATISTIK_MAX);
				warteAufTaste();
				break;
			case '5':
				printf("Sortierte Ausgabe:\n\n");
				{
					// Kopie des Arrays anlegen:
					int zahlenKopie[MAX];
					for (i=0; i<MAX; i++) zahlenKopie[i] = zahlen[i];

					// mit der Kopie agieren:
					arraySortieren(&zahlenKopie[0], MAX);
					arrayAusgeben(&zahlenKopie[0], MAX);

					warteAufTaste();
				}
				break;
			case '6':
				zahlAendern(&zahlen[0], MAX);
				warteAufTaste();
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
	printf("\t3\tkleinste Zahl ausgeben\n");
	printf("\t4\tgrößte Zahl ausgeben\n");
	printf("\t5\tZahlen sortiert ausgeben\n");
	printf("\t6\tEine Zahl ändern\n");
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
void zahlAendern(int* pArray, int n) {
	int idx, neuerWert;
	do {
		printf("Die Zahl an welcher Position wollen Sie verändern? (0..%d)\n", n-1);
		idx = (int)fliesskommaEingabe(2,0);
	} while (idx < 0 || idx > n-1);

	printf("Mit welcher Zahl wollen Sie die aktuelle (%d) ersetzen?\n", *(pArray+idx));
	neuerWert = (int)fliesskommaEingabe(MAX_INPUT_LENGTH,0); // aus lib/texteingabe.c

	// das eigentliche Array verändern:
	*(pArray+idx) = neuerWert;

	printf("\nOkay - an Stelle [%3d] steht jetzt die Zahl %d.\n", idx, *(pArray+idx));
}


/**
 * @param pArray Zeiger auf ein int-Array
 * @param n Anzahl Elemente in diesem Array
 */
void arraySortieren(int* pArray, int n) {
	int i,j;
	for (i=0; i<n-1; i++) {
		for (j=i+1; j<n; j++) {
			if ( *(pArray+i) > *(pArray+j) ) {
				// Werte tauschen:
				int temp = *(pArray+j);
				*(pArray+j) = *(pArray+i);
				*(pArray+i) = temp;
			}
		}
	}
}


/**
 * @param pArray Zeiger auf ein int-Array
 * @param n Anzahl Elemente in diesem Array
 */
void arrayAusgeben(int* pArray, int n) {
	printf("Reihe mit %d Zahlen:\n\n", n);

	int i;
	for (i=0; i<n; i++) {
		printf("[%3d]\t%d\n", i, *(pArray+i));
	}
}

/**
 * @param pArray Zeiger auf ein int-Array
 * @param n Anzahl Elemente in diesem Array
 * @param modus eine der vordefinierten Konstanten STATISTIK_*
 */
void statistikAusgeben(int* pArray, int n, int modus) {
	switch(modus) {
		case STATISTIK_MIN:
		case STATISTIK_MAX:
			// nach einem einzelnen Wert suchen:
			{
				int wert, pos, i;
				wert = *(pArray+0); pos = 0; // vom ersten Wert ausgehen
				for (i=0; i<n; i++) {
					int kandidat = *(pArray+i);
					int treffer = 0;
					if (modus == STATISTIK_MAX && kandidat > wert) treffer = -1;
					if (modus == STATISTIK_MIN && kandidat < wert) treffer = -1;

					if (treffer) {
						wert = kandidat;
						pos = i;
					}
				}
				// das Ergebnis ausgeben:
				if (modus == STATISTIK_MIN) {
					printf("Die kleinste Zahl ist %d an Position [%3d]", wert, pos);
				} else if (modus == STATISTIK_MAX) {
					printf("Die größte Zahl ist %d an Position [%3d]", wert, pos);
				} else {
					// das sollte nie passieren:
					fprintf(stderr, "Programmfehler in %s:%d!\n", __FILE__, __LINE__);
				}
			}

			break;
		default:
			// kein implementierter Modus:
			fprintf(stderr, "Programmfehler: Die Funktion statistikAusgeben() kennt keinen Modus Nr. %d ...\n", modus);
	}
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

