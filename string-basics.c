#include <stdio.h>
#include "lib/dump.c"
#include "lib/texteingabe.c"

#define MAX_STRING_LENGTH 255

char* zeichenkette(void);
char* eingabeZeichenkette(void);
void meinStrCat(void);
int laenge(char*);
void anhaengen(char*, char*, char*);

int main(void) {

//	char satz[17];
//	printf("Bitte geben Sie einen Satz ein: ");
//	scanf("%s", &satz);

	char satz[] = "Heute ist Donnerstag.\0";
	char satz2[] = "Das ist ein anderer, sehr viel längerer Satz.\0";

	printf("Satz ist am Anfang %d Zeichen lang, Satz 2 %d.\n", laenge(&satz[0]), laenge(&satz2[0]));

	// jetzt überschreiben wir die Variable satz mit satz2 -
	// der reservierte Speicher von satz reicht dafür nicht aus!
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

	printf("Variable satz ist %ld Bytes groß.\n", sizeof(satz));
	printf("Variable satz2 ist %ld Bytes groß.\n", sizeof(satz2));

	dump(satz2);

	printf("Ausgabe: %s\n", zeichenkette());
	dump(zeichenkette());

	printf("Strings zusammenbasteln ohne string.h ...\n");
	meinStrCat();
}

void meinStrCat() {
	int i;

	char puffer[MAX_STRING_LENGTH + 1];
	char space = ' ';
	// auf jeden Fall 0-Bytes im Puffer:
	for (i=0; i<MAX_STRING_LENGTH+1; i++) puffer[i] = '\0';

	printf("Bitte geben Sie eine Zeichenkette ein:\n");
	char* eingabe = eingabeZeichenkette();
	printf("Ihre Eingabe: %s\n", eingabe);

	anhaengen(puffer, puffer, "Heute");
	anhaengen(puffer, puffer, &space);
	anhaengen(puffer, puffer, "ist");
	anhaengen(puffer, puffer, &space);
	anhaengen(puffer, puffer, "Mittwoch:");
	anhaengen(puffer, puffer, &space);
	anhaengen(puffer, puffer, eingabe);

	printf("Sie haben diesen schönen Satz gewonnen: \n%s\n", puffer);
	dump(puffer);
}

int laenge(char* s) {
	int i=0;
	for (; *(s+i) != '\0' ; i++);
	return i;
}

void anhaengen(char* ziel, char* teil1, char* teil2) {
	int l1 = laenge(teil1);
	int l2 = laenge(teil2);

	int zielCursor = 0;

	int i=0;
	for (; i<l1; i++) {
		ziel[zielCursor] = teil1[i];
		zielCursor++;
		if (zielCursor >= MAX_STRING_LENGTH) return;
	}

	i=0;
	for (; i<l2; i++) {
		ziel[zielCursor] = teil2[i];
		zielCursor++;
		if (zielCursor >= MAX_STRING_LENGTH) return;
	}

	ziel[zielCursor] = '\0';
}


char* eingabeZeichenkette(void) {
	return texteingabeLength(MAX_STRING_LENGTH); // aus lib/texteingabe.c
}

char* zeichenkette(void) {
	static char text[] = "Mir ist warm.";
	// return &text[0];
	char *ptrText = &text[0];
	printf("In der Funktion zeichenkette() ist text: %s\n", ptrText);
	printf("Die Adresse von text ist: 0x%lx.\n", (long)ptrText);
	return ptrText;
}
