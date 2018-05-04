#include <stdio.h>
#ifdef _WIN32
#include <conio.h>
#endif
#ifdef __linux__
#include "./getch.c"
#endif

#define TEXTEINGABE_BUFFER_SIZE 32

char * texteingabe(void) {
	static char buffer[TEXTEINGABE_BUFFER_SIZE];
	int cursor = 0;
	char c;

	while(1) {
		c = getch(); // printf("%d ", c); // debug output

		// Auf Steuerzeichen prüfen:
		if (c == 13 || c == 10) {
			// Eingabe abschließen
			break;
		} else if (c == 8 || c == 127) {
			// Backspace
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

			cursor --;
			buffer[cursor] = 0;
		} else {
			// okay, kein Steuerzeichen...
			if (cursor >= TEXTEINGABE_BUFFER_SIZE - 1) {
				// kein Platz mehr - ignorieren...
			} else {
				// das Zeichen wird angehängt:
				printf("%c", c);
				buffer[cursor] = c;
				cursor ++;
			}
		}

	}

	buffer[cursor] = '\0'; // Wir bauen ordentliche 0-terminierte Strings...
	printf("\n");

	return &buffer[0];
}

