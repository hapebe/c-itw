/*
 * bubblesort2.c
 * 
 * 2018 by Hans-Peter Bergner <hapebe@gmx.de>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h> // für atoi()
#include <string.h> // für strcmp()

int main(int argc, char *argv[]) {
	// Sonderfall: --help ?
	if ((argc == 2) && !strcmp(argv[1], "--help")) {
		fprintf(stderr, "bubblesort2 is a very simple program made for educational purposes \n");
		fprintf(stderr, "of its author. All it can do is to sort sequences of integer numbers, \n");
		fprintf(stderr, "and display the sorted sequence along with the original positions of \n");
		fprintf(stderr, "the numbers.\n");
		fprintf(stderr, "WARNING: It does not have adequate error handling!\n\n");
		fprintf(stderr, "Usage:\n\n");
		fprintf(stderr, "(A) bubblesort2\n");
		fprintf(stderr, "    (fully interactive mode) \n");
		fprintf(stderr, "    You will be asked to enter the length of a number sequence \n");
		fprintf(stderr, "    first, aside from that it will work like usage (B).\n\n");
		fprintf(stderr, "(B) bubblesort2 <N>\n");
		fprintf(stderr, "    You will be asked to enter N numbers consecutively. They will \n");
		fprintf(stderr, "    be printed back and then sorted and displayed, along with their \n");
		fprintf(stderr, "    position in the original sequence.\n\n");
		fprintf(stderr, "(C) bubblesort2 <n0> <n1>[ n2][...][nN]\n");
		fprintf(stderr, "    (fully non-interactive mode) \n");
		fprintf(stderr, "    All arguments will be interpreted as a number sequence. They \n");
		fprintf(stderr, "    will be printed back and then sorted and displayed, along with \n");
		fprintf(stderr, "    their position in the original sequence.\n");
		fprintf(stderr, "    You can use this mode like e.g.:\n");
		fprintf(stderr, "        shuf -i 1-100 | xargs bubblesort2\n\n");
		return 0;
	}
	
	int i, j; // Zählvariablen
	
	// Länge der Zahlen-Sequenz bestimmen:
	int anzahl = 0;
	int vonARGV = 0;
	if (argc < 2) {
		printf("Wieviele Zahlen wollen Sie eingeben? ");
		scanf("%d", &anzahl);
	} else if (argc == 2) {
		anzahl = atoi(argv[1]);
	} else {
		// dann gehen wir davon aus, dass die Zahlenfolge direkt übergeben wurde:
		anzahl = argc - 1;
		vonARGV = -1;
	}
	if (anzahl < 1) {
		printf("Die Länge der Zahlen-Sequenz muss mindest 1 sein.\n");
		return 1;
	}
	
	// Zahlen-Sequenz anlegen:
	int zahlen[anzahl];
	
	// Zahlen einlesen:
	if (vonARGV) {
		// Argumente einlesen:
		for (i=1; i<argc; i++) {
			zahlen[i-1] = atoi(argv[i]);
		}
		printf("Das sind Ihre Zahlen:\n");
	} else {
		// manuell eingeben:
		printf("Bitte geben Sie %d Zahlen ein!\n", anzahl);
		for (i=0; i<anzahl; i++) {
			if (!vonARGV) printf("%d. Zahl: ", i+1);
			scanf("%i", &zahlen[i]);
		}
		printf("\nDanke - das sind Ihre Zahlen:\n");
	}
	
	
	// die ursprüngliche Position der Zahlen merken:
	int positionen[anzahl];
	for (i=0; i<anzahl; i++) positionen[i] = i;
	
	for (i=0; i<anzahl; i++) {
		printf("%d. Zahl:\t%d\n", positionen[i]+1, zahlen[i]);
	}
	
	// jetzt sortieren:
	for (i=0; i<anzahl-1; i++) {
		for (j=i+1; j<anzahl; j++) {
			if (zahlen[i]>zahlen[j]) {
				// Werte tauschen:
				int temp = zahlen[j];
				zahlen[j] = zahlen[i];
				zahlen[i] = temp;
				
				// Positionsnummern ebenfalls tauschen, so dass sie mit 
				// ihren Werten "zusammen bleiben":
				temp = positionen[j];
				positionen[j] = positionen[i];
				positionen[i] = temp;
			}
		}
	}

	printf("\nSortiert sehen sie so aus:\n");
	for (i=0; i<anzahl; i++) {
		printf("%d. Zahl:\t%d\n", positionen[i]+1, zahlen[i]);
	}
	
	return 0;
}

