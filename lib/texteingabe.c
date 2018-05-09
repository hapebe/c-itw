/**
 * Text-Eingabe-Funktionen auf Basis von "getch()", die die G�ltigkeit
 * von Eingaben zeichenweise pr�fen k�nnen, und ggf. ohne
 * <Eingabe>-Taste am Ende auskommen.
 *
 * *FIXME*
 * Unter Linux kommt die Behandlung von Backspace nicht mit Eingaben
 * klar, die l�nger als eine Bildschirmzeile sind.
 */

#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#endif
#ifdef __linux__
#include "./getch.c"
#endif

#define TEXTEINGABE_BUFFER_SIZE 257

// globale Variable, die zur Ver�nderung des Verhaltens von
// texteingabe() ge�ndert werden kann
int textEingabeAcceptEmpty = -1;


/**
 * @param set 0-terminierter String...
 * @return -1 if found, 0 if not found
 */
int setContainsAtom(char * set, char atom) {
	int i;
	for (i=0; set[i] != 0; i++) {
		if (set[i] == atom) return -1; // found!
	}
	return 0; // not found
}

char * texteingabeLengthSet(int maxLength, char * allowedCharSet) {
	// keine Buffer-Overruns akzeptieren: ggf. maxLength beschr�nken:
	if (maxLength > TEXTEINGABE_BUFFER_SIZE - 1) maxLength = TEXTEINGABE_BUFFER_SIZE - 1;

	static char buffer[TEXTEINGABE_BUFFER_SIZE]; // 1 char mehr, f�r die \0 am Ende
	int cursor = 0;
	char c;

	while(1) { // Endlosschleife, kann nur per "break;" verlassen werden

		c = getch();

		// Auf Steuerzeichen pr�fen:
		if (c == 13 || c == 10) {
			// Eingabe abschlie�en
			if (textEingabeAcceptEmpty || cursor > 0) break;
		} else if (c == 8 || c == 127) {
			// Backspace
			if (cursor > 0) {
				// nur dann verarbeiten, wenn wir tats�chlich mindesten ein Zeichen haben

				#ifdef _WIN32
				printf("%c %c",c ,c); // BS, Leerzeichen zum L�schen, wieder BS...
				#endif

				#ifdef __linux__
				// Unter Linux geht der Backspace-Support wohl nicht ohne \r oder explizite Positionierung des Cursors...
				int i;

				// Erste Runde: Alles (+1 Zeichen) mit Leerzeichen �berschreiben:
				printf("\r");
				for (i=0; i<cursor; i++) printf(" ");

				// Zweite Runde: Alles wieder hinschreiben:
				printf("\r");
				for (i=0; i<cursor-1; i++) {
					printf("%c", buffer[i]);
				}
				#endif

				// nach der grafischen Umsetzung - auch in der Datenstruktur umsetzen:
				cursor --; // Cursor eins in Richtung Anfang,
				buffer[cursor] = 0; // kein Zeichen an der Cursor-Position
			}
		} else {
			// also ein normales Text-Zeichen:

			// wenn das Zeichen erlaubt ist UND der String unter der erlaubten L�nge liegt:
			if (setContainsAtom(allowedCharSet, c) && (cursor < maxLength)) {
				// das Zeichen wird angeh�ngt:
				printf("%c", c);
				buffer[cursor] = c;
				cursor ++;
			} else {
				// nop - das Zeichen ignorieren
			}
		} // Ende Klassen-Unterscheidung der Eingabe

	} // Auf das n�chste Eingabezeichen warten

	buffer[cursor] = '\0'; // Wir bauen ordentliche 0-terminierte Strings...
	printf("\n");

	return &buffer[0];
}

char * texteingabeLength(int maxLength) {
	// wir erzeugen eine Menge erlaubter Zeichen:
	static char allowedCharSet[257];

	int pos = 0, i;
	for (i=32;i<127;i++) {
		// alle ASCII-Zeichen mit Codes zwischen 32 und 126 sind erlaubt
		allowedCharSet[pos] = i; pos++;
	}
	// TODO noch Umlaute etc. hinzuf�gen...
	allowedCharSet[pos] = 0; // 0-terminiert...

	return texteingabeLengthSet(maxLength, allowedCharSet);
}

char * texteingabe(void) {
	return texteingabeLength(TEXTEINGABE_BUFFER_SIZE - 1);
}

char * textEingabeEinZeichenOhneEcho(void) {
	static char buffer[2]; // 1 char mehr, f�r die \0 am Ende
	int cursor = 0;
	char c;

	while(1) { // Endlosschleife, kann nur per "break;" verlassen werden
		c = getch();

		// Auf Steuerzeichen pr�fen:
		if (c == 13 || c == 10) {
			// <Return> - Eingabe abschlie�en?
			if (textEingabeAcceptEmpty || cursor > 0) break;
		} else {
			// also ein "normales" Zeichen:
			buffer[cursor] = c;
			cursor ++;
		}

		if (cursor == 1) break; // wir haben ein Zeichen, let's go!

	} // Auf das n�chste Eingabezeichen warten

	buffer[cursor] = '\0'; // Wir bauen ordentliche 0-terminierte Strings...
	printf("\n");

	return &buffer[0];
}

char * textEingabeEinZeichenAusMengeOhneEcho(char * allowedCharSet) {
	static char buffer[2]; // 1 char mehr, f�r die \0 am Ende
	int cursor = 0;
	char c;

	while(1) { // Endlosschleife, kann nur per "break;" verlassen werden
		c = getch();

		// Auf Steuerzeichen pr�fen:
		if (c == 13 || c == 10) {
			// <Return> - Eingabe abschlie�en?
			if (textEingabeAcceptEmpty || cursor > 0) break;
		} else {
			// also ein "normales" Zeichen:

			// wenn das Zeichen erlaubt ist:
			if (setContainsAtom(allowedCharSet, c)) {
				// das Zeichen wird angeh�ngt:
				buffer[cursor] = c;
				cursor ++;
			}
		}

		if (cursor == 1) break; // wir haben ein Zeichen, let's go!

	} // Auf das n�chste Eingabezeichen warten

	buffer[cursor] = '\0'; // Wir bauen ordentliche 0-terminierte Strings...
	printf("\n");

	return &buffer[0];
}


