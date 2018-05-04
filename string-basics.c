#include <stdio.h>
#include "lib/dump.c"

int main(void) {
	
//	char satz[17];
//	printf("Bitte geben Sie einen Satz ein: ");
//	scanf("%s", &satz);
	
	char satz[] = "Heute ist Donnerstag.\0";
	char satz2[] = "Das ist ein anderer, sehr viel l�ngerer Satz.\0";
	
	// jetzt �berschreiben wir die Variable satz mit satz2 - 
	// der reservierte Speicher von satz reicht daf�r nicht aus!
	int i=0;
	for (i=0; i<sizeof(satz2); i++) {
		satz[i] = satz2[i];
	}
	
	i=0;
	for (i=0; i<64; i++) {
		printf("%c", satz[i]);
	}
	
	printf("\nDies ist Ihr Satz: %s\n", satz);
	printf("\nDies ist Ihr Satz2: %s\n", satz2);
	
	printf("Variable satz ist %d Bytes gro�.\n", sizeof(satz));
	printf("Variable satz2 ist %d Bytes gro�.\n", sizeof(satz2));
	
	dump(satz2);
}


