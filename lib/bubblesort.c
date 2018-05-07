#include <stdio.h>

/**
 * sortiert anzahl Elemente von zahlen garantiert aufsteigend.
 */

// globale Variablen zur Performance-Beurteilung:
long bubbleOuterCount = 0, bubbleInnerCount = 0, bubbleSwapCount = 0;

void bubblesort(int zahlen[], int anzahl) {
	int i, j; // Schleifenzähler-Variablen
	int temp; // wird zum Tauschen zweier Werte benötigt

	// maximal brauchen wir N-1 Durchgänge
	for (i=0; i < anzahl-1; i++) {
		#ifdef DEBUG
		printf("Äußere Schleife %d:\n", i+1);
		#endif

		bubbleOuterCount ++;
		long innerSwapCount = 0;
		// Bubble sort: die größte Zahl steigt garantiert ans Ende auf;
		// daher müssen wir nach N Durchgängen N Zahlen am Ende nicht
		// mehr betrachten.
		for (j=0; j < anzahl-i-1; j++) {
			bubbleInnerCount ++;
			if (bubbleInnerCount % 100000000 == 0) printf("%ldM innere Schleifen absolviert...\n", bubbleInnerCount/1000000l);

			if (zahlen[j] > zahlen[j+1]) {
				// okay, es folgt eine kleinere Zahl auf eine größere,
				// wir müssen sie tauschen:
				temp = zahlen[j];
				zahlen[j] = zahlen[j+1];
				zahlen[j+1] = temp;

				bubbleSwapCount ++;
				innerSwapCount ++;

				// Debug-Ausgabe:
				#ifdef DEBUG
				printf("Habe den %d. und %d. Wert vertauscht: ", j, j+1);
				print_int_array(zahlen, anzahl);
				#endif
			}
		}
		if (innerSwapCount == 0) {
			#ifdef DEBUG
			printf("In diesem Durchgang wurden keine Werte getauscht - wir sind also fertig!\n");
			#endif
			break;
		}
	}


}
