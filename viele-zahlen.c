#include <stdio.h>

#define ANZAHL 100000
// #define DEBUG 0

// forward declaration (die eigentliche Implementierung folgt unten):
void print_int_array(int* zahlen, int n);

int main(void)
{
	int zahlen[ANZAHL];

	// Eingabe:
	printf("Bitte geben Sie %d Zahlen ein:\n", ANZAHL);
	int i=0;
	for (i=0; i<ANZAHL; i++) {
		printf("%d. : ", (i+1));
		scanf("%i", &zahlen[i]);
	}
	printf("\nDanke.\n\n");

	// Ausgabe:
	i=0;
	printf("Hier kommen Ihre Zahlen:\n");
	print_int_array(zahlen, ANZAHL);
	//~ do {
		//~ printf("%i", zahlen[i]);
		//~ i++;
		//~ if (i<ANZAHL) printf(", ");
	//~ } while (i<ANZAHL);
	//~ printf("\n");

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

	// sortieren:
	int j; // zweite Schleifenzähler-Variable
	int temp; // wird zum Tauschen zweier Werte benötigt
	long outerCount = 0, innerCount = 0;
	long swapCount = 0, innerSwapCount = 0;

	// maximal brauchen wir N-1 Durchgänge
	for (i=0; i < ANZAHL-1; i++) {
		#ifdef DEBUG
		printf("Äußere Schleife %d:\n", i+1);
		#endif

		outerCount ++;
		innerSwapCount = 0;
		// Bubble sort: die größte Zahl steigt garantiert ans Ende auf;
		// daher müssen wir nach N Durchgängen N Zahlen am Ende nicht
		// mehr betrachten.
		for (j=0; j < ANZAHL-i-1; j++) {
			innerCount ++;
			if (innerCount % 1000000 == 0) printf("%ldM innere Schleifen absolviert...\n", innerCount/1000000l);

			if (zahlen[j] > zahlen[j+1]) {
				// okay, es folgt eine kleinere Zahl auf eine größere,
				// wir müssen sie tauschen:
				temp = zahlen[j];
				zahlen[j] = zahlen[j+1];
				zahlen[j+1] = temp;

				swapCount ++;
				innerSwapCount ++;

				// Debug-Ausgabe:
				#ifdef DEBUG
				printf("Habe den %d. und %d. Wert vertauscht: ", j, j+1);
				print_int_array(zahlen, ANZAHL);
				#endif
			}
		}
		if (innerSwapCount == 0) {
			printf("In diesem Durchgang wurden keine Werte getauscht - wir sind also fertig!\n");
			break;
		}
	}
	// Ausgabe:
	i=0;
	printf("Hier kommen Ihre sortierten Zahlen:\n");
	print_int_array(zahlen, ANZAHL);
	printf("Performance: %ld äußere Durchläufe, %ld innere Durchläufe, %ld Vertauschungen.\n", outerCount, innerCount, swapCount);


	// Fertig:
	printf("Pause!\n");
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
