#include <stdio.h>
#include "lib/texteingabe.c"

int myStrLen(char* str) {
	// Wie ich gelernt habe, kann man Pointer auf einen Datentyp auch
	// direkt als Array verwenden.
	// Für jeden Index-Wert wird dabei die Länge des Datentypen zum
	// eigentlichen Wert des Zeigers addiert - bei char also einfach eins,
	// bei int (32 Bit) aber z.B. vier.

	int i;
	for (i=0; str[i] != 0; i++) { ;	}
	return i;
}

int main(void) {
	char * eingabe;

	printf("Test: Es sollen maximal 8 Zeichen aus der Menge (1234) eingegeben werden:\n");
	eingabe = texteingabeLengthSet(8, (char[]){'1','2','3','4','\0'});
	printf("Ihre Eingabe: %s (L: %d)\n", eingabe, myStrLen(eingabe));

	printf("Test: Keine Einschränkungen der Eingabe - maximale Länge ist also %d.\n", TEXTEINGABE_BUFFER_SIZE - 1);
	eingabe = texteingabe();
	printf("Ihre Eingabe: %s (L: %d)\n", eingabe, myStrLen(eingabe));

	printf("Test: Es sollen maximal 8 Zeichen aus der Menge (01olOL) eingegeben werden, eine leere Eingabe soll nicht möglich sein:\n");
	int temp = textEingabeAcceptEmpty;
	textEingabeAcceptEmpty = 0;
	eingabe = texteingabeLengthSet(8, (char[]){'0','1','o','l','O','L','\0'});
	printf("Ihre Eingabe: %s (L: %d)\n", eingabe, myStrLen(eingabe));
	textEingabeAcceptEmpty = temp; // alten Status wiederherstellen
}
