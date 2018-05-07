#include "debug-switch.c"
#include <stdio.h>
#include <string.h> // für strcmp()
#include "lib/hapebe-shared.h" // für print_int_array()
#include "lib/bubblesort.c"
#include "lib/quicksort.c"

#define ANZAHL 1000000

// nächste Zeile auskommentieren: Die eigentlichen Zahlen werden dann
// gar nicht mehr ausgegeben (für Performance-Messungen)
// #define ZAHLENAUSGABE -1

#define MODE_BUBBLESORT 1
#define MODE_QUICKSORT 2
int modus = MODE_BUBBLESORT;

int main(int argc, char *argv[]) {

	// Haben wir ein Argument?
	if (argc > 1) {
		if (!strcmp("qs", argv[1])) {
			modus = MODE_QUICKSORT;
		}
	}

	int zahlen[ANZAHL];
	int zahlenKopie[ANZAHL];

	// Eingabe:
	printf("Bitte geben Sie %d Zahlen ein:\n", ANZAHL);
	int i=0;
	for (i=0; i<ANZAHL; i++) {
		printf("%d. : ", (i+1));
		scanf("%i", &zahlen[i]);
	}
	printf("\nDanke.\n\n");

#ifdef ZAHLENAUSGABE
	// Ausgabe:
	printf("Hier kommen Ihre Zahlen:\n");
	print_int_array(zahlen, ANZAHL);

	// kleinste Zahl:
	int min = zahlen[0];
	int minIdx = 0;
	for (i=0; i<ANZAHL; i++) {
		if (zahlen[i] < min) {
			min = zahlen[i];
			minIdx = i;
		}
	}
	printf("Die kleinste Zahl davon ist: %d an %d. Stelle.\n", min, minIdx+1);

	// größte Zahl:
	int max = zahlen[0];
	int maxIdx = 0;
	for (i=0; i<ANZAHL; i++) {
		if (zahlen[i] > max) {
			max = zahlen[i];
			maxIdx = i;
		}
	}
	printf("Die größte Zahl davon ist: %d an %d. Stelle.\n", max, maxIdx+1);
#endif

	if (modus == MODE_BUBBLESORT) {
		// Bubble Sort:
		for (i=0; i<ANZAHL; i++) zahlenKopie[i] = zahlen[i];
		printf("\nSortieren mit BubbleSort:\n");
		bubblesort(zahlenKopie, ANZAHL);
	#ifdef ZAHLENAUSGABE
		print_int_array(zahlenKopie, ANZAHL);
	#endif
		printf("Performance: %ld äußere Durchläufe, %ld innere Durchläufe, %ld Vertauschungen.\n",
			bubbleOuterCount, bubbleInnerCount, bubbleSwapCount);
	}

	if (modus == MODE_QUICKSORT) {
		// Quicksort:
		for (i=0; i<ANZAHL; i++) zahlenKopie[i] = zahlen[i];
		printf("\nSortieren mit QuickSort:\n");
		quicksort(zahlenKopie, 0, ANZAHL - 1, 0);
	#ifdef ZAHLENAUSGABE
		print_int_array(zahlenKopie, ANZAHL);
	#endif
		printf("Performance: %ld Aufrufe der Funktion (max. Tiefe: %ld), %ld Vertauschungen.\n",
			qsCallCount, qsMaxRecurseDepth, qsSwapCount);
	}

	return 0;
}

void print_int_array(int* zahlen, int n) {
	int i;
	for (i=0; i<n; i++) {
		printf("%i", *zahlen);
		if (i < n-1) printf(", ");

		// Pointer auf nächsten Array-Eintrag setzen; also Adresse um
		// Länge einer int-Variablen erhöhen:

		// printf("Pointer vor dem Inkrement: 0x%p ; ", (void *)zahlen);
		zahlen += 1;
		// printf("danach: 0x%p \n", (void *)zahlen);
	}
	printf("\n");
}
