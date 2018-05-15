/**
 * Text-Eingabe-Funktionen auf Basis von "getch()", die die Gültigkeit
 * von Eingaben zeichenweise prüfen können, und ggf. ohne
 * <Eingabe>-Taste am Ende auskommen.
 *
 * *FIXME*
 * Unter Linux kommt die Behandlung von Backspace nicht mit Eingaben
 * klar, die länger als eine Bildschirmzeile sind.
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#endif
#ifdef __linux__
#include "./getch.c"
#endif

#define TEXTEINGABE_BUFFER_SIZE 257

#define DEZIMAL_ZIFFERN (char[]){ '0','1','2','3','4','5','6','7','8','9','\0' }
#define KOMMA_ZEICHEN (char[]){ '.',',','\0' }
#define NEGATIV_ZEICHEN (char[]){ '-','\0' }

// globale Variable, die zur Veränderung des Verhaltens von
// texteingabe() geändert werden kann
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
	// keine Buffer-Overruns akzeptieren: ggf. maxLength beschränken:
	if (maxLength > TEXTEINGABE_BUFFER_SIZE - 1) maxLength = TEXTEINGABE_BUFFER_SIZE - 1;

	static char buffer[TEXTEINGABE_BUFFER_SIZE]; // 1 char mehr, für die \0 am Ende
	int cursor = 0;
	char c;

	while(1) { // Endlosschleife, kann nur per "break;" verlassen werden

		c = getch();

		// Auf Steuerzeichen prüfen:
		if (c == 13 || c == 10) {
			// Eingabe abschließen
			if (textEingabeAcceptEmpty || cursor > 0) break;
		} else if (c == 8 || c == 127) {
			// Backspace
			if (cursor > 0) {
				// nur dann verarbeiten, wenn wir tatsächlich mindesten ein Zeichen haben

				#ifdef _WIN32
				printf("%c %c",c ,c); // BS, Leerzeichen zum Löschen, wieder BS...
				#endif

				#ifdef __linux__
				// Unter Linux geht der Backspace-Support wohl nicht ohne \r oder explizite Positionierung des Cursors...
				int i;

				// Erste Runde: Alles (+1 Zeichen) mit Leerzeichen überschreiben:
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

			// wenn das Zeichen erlaubt ist UND der String unter der erlaubten Länge liegt:
			if (setContainsAtom(allowedCharSet, c) && (cursor < maxLength)) {
				// das Zeichen wird angehängt:
				printf("%c", c);
				buffer[cursor] = c;
				cursor ++;
			} else {
				// nop - das Zeichen ignorieren
			}
		} // Ende Klassen-Unterscheidung der Eingabe

	} // Auf das nächste Eingabezeichen warten

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
	// TODO noch Umlaute etc. hinzufügen...
	allowedCharSet[pos] = 0; // 0-terminiert...

	return texteingabeLengthSet(maxLength, allowedCharSet);
}

char * texteingabe(void) {
	return texteingabeLength(TEXTEINGABE_BUFFER_SIZE - 1);
}

char * textEingabeEinZeichenOhneEcho(void) {
	static char buffer[2]; // 1 char mehr, für die \0 am Ende
	int cursor = 0;
	char c;

	while(1) { // Endlosschleife, kann nur per "break;" verlassen werden
		c = getch();

		// Auf Steuerzeichen prüfen:
		if (c == 13 || c == 10) {
			// <Return> - Eingabe abschließen?
			if (textEingabeAcceptEmpty || cursor > 0) break;
		} else {
			// also ein "normales" Zeichen:
			buffer[cursor] = c;
			cursor ++;
		}

		if (cursor == 1) break; // wir haben ein Zeichen, let's go!

	} // Auf das nächste Eingabezeichen warten

	buffer[cursor] = '\0'; // Wir bauen ordentliche 0-terminierte Strings...
	printf("\n");

	return &buffer[0];
}

char * textEingabeEinZeichenAusMengeOhneEcho(char * allowedCharSet) {
	static char buffer[2]; // 1 char mehr, für die \0 am Ende
	int cursor = 0;
	char c;

	while(1) { // Endlosschleife, kann nur per "break;" verlassen werden
		c = getch();

		// Auf Steuerzeichen prüfen:
		if (c == 13 || c == 10) {
			// <Return> - Eingabe abschließen?
			if (textEingabeAcceptEmpty || cursor > 0) break;
		} else {
			// also ein "normales" Zeichen:

			// wenn das Zeichen erlaubt ist:
			if (setContainsAtom(allowedCharSet, c)) {
				// das Zeichen wird angehängt:
				buffer[cursor] = c;
				cursor ++;
			}
		}

		if (cursor == 1) break; // wir haben ein Zeichen, let's go!

	} // Auf das nächste Eingabezeichen warten

	buffer[cursor] = '\0'; // Wir bauen ordentliche 0-terminierte Strings...
	printf("\n");

	return &buffer[0];
}

/**
 * @return position von needle in haystack, oder -1, wenn das Zeichen nicht enthalten ist
 */
int strpos(char needle, char* haystack) {
	int i;
	for (i=0; haystack[i] != '\0';i++) {
		if (haystack[i] == needle) return i;
	}
	return -1; // nicht enthalten!
}

/**
 * spezialisierte Eingabe-Funktion laut Aufgabe am 15.05.2018
 *
 * akzeptiert positive und negative Fließkomma- und Ganzzahlen mit einer
 * festgelegten maximalen Anzahl Vor- und Nachkommastellen.
 *
 * akzeptiert kein führendes Komma
 */
double fliesskommaEingabe(int maxVorKommaStellen, int maxNachKommaStellen) {
	if (maxVorKommaStellen < 1) {
		fprintf(stderr, "Es muss mindestens eine Vorkomma-Stelle erlaubt sein.");
		exit(1);
	}

	int maxLength = maxVorKommaStellen + maxNachKommaStellen + 2;
		// keine Buffer-Overruns akzeptieren: ggf. maxLength beschränken:
		if (maxLength > TEXTEINGABE_BUFFER_SIZE - 1) maxLength = TEXTEINGABE_BUFFER_SIZE - 1;

	static char buffer[TEXTEINGABE_BUFFER_SIZE]; // 1 char mehr, für die \0 am Ende
	int i=0;
	// den Puffer löschen, sicher ist sicher...
	for (i=0; i<TEXTEINGABE_BUFFER_SIZE; i++) buffer[i] = '\0';


	int cursor = 0;
	char c;

	// Status der aktuellen Eingabe:
	int kommaPos = -1;
	int istNegativ = 0;
	int fuehrendeNull = 0;
	int vorKommaStellen = 0;
	int nachKommaStellen = 0;

	while(1) { // Endlosschleife, kann nur per "break;" verlassen werden

		c = getch();

		// Auf Steuerzeichen prüfen:
		if (c == 13 || c == 10) {
			// Eingabe abschließen
			if (textEingabeAcceptEmpty || cursor > 0) break;
		} else if (c == 8 || c == 127) {
			// Backspace
			if (cursor > 0) {
				// nur dann verarbeiten, wenn wir tatsächlich mindesten ein Zeichen haben

				#ifdef _WIN32
				printf("%c %c",c ,c); // BS, Leerzeichen zum Löschen, wieder BS...
				#endif

				#ifdef __linux__
				// Unter Linux geht der Backspace-Support wohl nicht ohne \r oder explizite Positionierung des Cursors...
				int i;

				// Erste Runde: Alles (+1 Zeichen) mit Leerzeichen überschreiben:
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
		} else if (setContainsAtom(NEGATIV_ZEICHEN, c) && cursor == 0) {
			// Minus-Zeichen an erster Stelle ist okay:
			printf("%c", c);
			buffer[cursor] = c;
			cursor ++;
		} else if (cursor < maxLength) {
			// also ein normales Text-Zeichen, und die Länge ist unter Maximum:

			// wenn das Zeichen erlaubt ist:
			if (setContainsAtom(DEZIMAL_ZIFFERN, c)) {
				int okay = -1;
				if (kommaPos < 0) {
					// es wäre eine Vorkommastelle:
					if (vorKommaStellen >= maxVorKommaStellen) okay = 0;
				} else {
					// es wäre eine Nachkommastelle:
					if (nachKommaStellen >= maxNachKommaStellen) okay = 0;
				}
				if (fuehrendeNull && kommaPos < 0) okay = 0; // Ziffer würde ohne Komma auf führende Null folgen...
				if (okay) {
					// das Zeichen wird angehängt:
					printf("%c", c);
					buffer[cursor] = c;
					cursor ++;
				} else {
					// nop - wegen Stellenbeschränkung ignorieren
				}
			} else if (
				setContainsAtom(KOMMA_ZEICHEN, c) // wäre ein Komma,
				&& cursor > (istNegativ?1:0) // wäre kein führendes Komma,
				&& kommaPos < 0 // es gibt noch kein Komma,
				&& maxNachKommaStellen > 0 // und es dürfen generell Nachkommastellen eingegeben werden.
			) {
				// ein Komma wird angehängt:
				c = '.';
				printf("%c", c);
				buffer[cursor] = c;
				cursor ++;
			} else {
				// nop - das Zeichen ignorieren
			}
		} // Ende Klassen-Unterscheidung der Eingabe

		// jedes Mal den "Status" der eingegebenen Zahl aktulisieren:
		istNegativ = (strpos('-', buffer) == 0);
		fuehrendeNull = (strpos('0', buffer) == (istNegativ?1:0));
		// schauen, ob wir schon oder noch ein Komma haben:
		kommaPos = strpos('.', buffer);

		if (kommaPos < 0) {
			// es gibt gar kein Komma in der Eingabe:
			vorKommaStellen = cursor;
			nachKommaStellen = 0;
		} else {
			vorKommaStellen = kommaPos;
			nachKommaStellen = cursor - kommaPos - 1;
		}
		if (istNegativ) vorKommaStellen --;

	} // Auf das nächste Eingabezeichen warten

	// Eingabe abschließen:
	printf("\n");
	buffer[cursor] = '\0'; // wir bauen ordentliche 0-terminierte Strings...


	// Rückgabewert berechnen:
	double retval = 0.0d;

	// Vorkomma-Anteil:
	int vordersteZiffer = 0;
	if (istNegativ) vordersteZiffer = 1;
	int hintersteZiffer = vordersteZiffer + vorKommaStellen - 1;
		// printf("Vorkomma-Teil von %d bis %d...\n", vordersteZiffer, hintersteZiffer);
	double stellenWert = 1.0d;
	for (i=hintersteZiffer; i>=vordersteZiffer; i--) {
		retval += ((int)buffer[i]-48) * stellenWert;
		stellenWert *= 10.0d; // ein Stelle nach links...
	}

	// Nachkomma-Anteil:
	vordersteZiffer = kommaPos+1;
	hintersteZiffer = vordersteZiffer + nachKommaStellen - 1;
		// if (vordersteZiffer <= hintersteZiffer) printf("Nachkomma-Teil von %d bis %d...\n", vordersteZiffer, hintersteZiffer);
	stellenWert = 1.0/10.0d;
	for (i=vordersteZiffer; i <= hintersteZiffer; i++) {
		retval += ((int)buffer[i]-48) * stellenWert; // Ziffer an #(kommaPos+1)+i
		stellenWert /= 10.0d; // ein Stelle nach rechts...
	}

	if (istNegativ) retval *= -1.0d;

	return retval;
}


