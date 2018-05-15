#include <stdio.h>
#include "lib/texteingabe.c"
#include "lib/baseconv.c"

#define ANZAHL 4
#define MAX_HEX_LAENGE 4

int eHex(int); // Deklaration der Funktion

int main(int argc, char** argv) {
	// Voraussetzung für die Funktionen in lib/baseconv.c:
	initReverseCharPool();

	printf("Die Summe der %d Hexadezimalzahlen ist: %d\n", ANZAHL, eHex(ANZAHL));
	return 0;
}

/**
 * nimmt <anzahl> Hexadezimalzahlen als Eingabe entgegen und gibt deren
 * Summe als int-Wert zurück.
 */
int eHex(int anzahl) { // Definition der Funktion
	int retval = 0; // Variable für die Summe, die am Ende zurückgegeben werden soll

	int i;
	for (i=0; i<anzahl; i++) {
		printf("Bitte geben Sie die %d. Zahl ein:\n", i+1);

		// Helfer-Funktion aus früheren Übungen: Text-Eingabe mit
		// Begrenzung der Länge und der erlaubten Zeichen:
		char* hexInput = texteingabeLengthSet( // in lib/texteingabe.c
			MAX_HEX_LAENGE, // maximale Eingabe-Länge
			&(char[]){ // die Adresse des ersten Elements einer Menge erlaubter Zeichen - das Ende der Menge wird mit einem Null-Byte markiert.
				'-',
				'0','1','2','3','4','5','6','7','8','9',
				'a','b','c','d','e','f',
				'A','B','C','D','E','F',
				'\0'
			}[0]
		); // Ende Funktionsaufruf von texteingabeLengthSet(..., ...)

		// Helfer-Funktion aus früheren Übungen: Umwandeln einer
		// symbolischen Zahl mit beliebigem Basis-System in einen
		// int-Wert:
		int wert = getNumericIntBase(hexInput, 16); // in lib/baseconv.c

		retval += wert; // diese eine Zahl zur Summe addieren
	}

	return retval;
}
