/*
 * bubblesort.c
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
#define ANZAHL 10

int main(int argc, char **argv) {
	int i, j; // Zählvariablen
	
	int zahlen[ANZAHL];
	
	printf("Bitte geben Sie %d Zahlen ein!\n", ANZAHL);
	for (i=0; i<ANZAHL; i++) {
		printf("%d. Zahl: ", i+1);
		scanf("%i", &zahlen[i]);
	}
	// die ursprüngliche Position der Zahlen merken:
	int positionen[ANZAHL];
	for (i=0; i<ANZAHL; i++) positionen[i] = i;
	
	printf("\nDanke - das sind Ihre Zahlen:\n");
	for (i=0; i<ANZAHL; i++) {
		printf("%d. Zahl:\t%d\n", positionen[i]+1, zahlen[i]);
	}
	
	// jetzt sortieren:
	for (i=0; i<ANZAHL-1; i++) {
		for (j=i+1; j<ANZAHL; j++) {
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

	printf("\nSortiert sehen Sie so aus:\n");
	for (i=0; i<ANZAHL; i++) {
		printf("%d. Zahl:\t%d\n", positionen[i]+1, zahlen[i]);
	}
	
	return 0;
}

