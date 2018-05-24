/**
 * Zweite Experimente mit struct - dieses Programm kann/soll mit
 * vorgefertigten Eingaben aus der Datei
 *
 * extra/struct1-eingabe
 *
 * getestet werden.
 *
 * ( ./struct1 < extra/struct1-eingabe )
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define N_PKW 3

struct pkw {
	char marke[30];
	char farbe[30];
	int alter;
};

/**
 * merken, ob wir mit Eingabe-Umleitung arbeiten - in diesem Fall werden
 * die Eingabe-Prompts unterdrückt.
 */
int ttyMode = -1;

char *trim(char *str);
void scanPkw(struct pkw * p);
void printPkw(struct pkw * p);

int main(int argc, char** argv) {
	// Laufen wir "interaktiv"?
	// Quelle: https://stackoverflow.com/questions/1312922/detect-if-stdin-is-a-terminal-or-pipe
	ttyMode = isatty(fileno(stdin)) ? -1 : 0;

	struct pkw fzg[N_PKW];

	int i=0;
	for (i=0; i<N_PKW; i++) {
		if (ttyMode) printf("Bitte geben Sie das %d. Fahrzeug ein!\n", i+1);
		scanPkw(&fzg[i]);
	}
	if (ttyMode) printf("\n");

	printf("Das sind Ihre %d Fahrzeuge:\n", N_PKW);
	for (i=0; i<N_PKW; i++) {
		printf("%d. ", (i+1));
		printPkw(&fzg[i]);
	}

	return 0;
}

void scanPkw(struct pkw * p) {
	char puffer[256];
	char* ptrPuffer = &puffer[0];
	char* trimmed;

	if (ttyMode) printf("Marke: ");
	fgets(puffer, 30, stdin);
	trimmed = trim(puffer);
	strcpy((*p).marke, trimmed); // Syntax 1 für Zeiger-Verweis auf Struktur-Element

	if (ttyMode) printf("Farbe: ");
	fgets(puffer, 30, stdin);
	trimmed = trim(puffer);
	strcpy(p->farbe, trimmed); // Syntax 2 für Zeiger-Verweis auf Struktur-Element

	if (ttyMode) printf("Alter: ");
	// auskommentiert und ersetzt, weil ich mit getch() keine
	// Eingabe-Umlenkung zum Testen benutzen kann:
	// p->alter = fliesskommaEingabe(3,0);
	fgets(ptrPuffer, 15, stdin);
	trimmed = trim(ptrPuffer);
	p->alter = atoi(trimmed);

}

void printPkw(struct pkw * p) {
	printf("Marke: %s, Farbe: %s, Alter: %d\n", p->marke, p->farbe, p->alter);
}


// source: https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
//
// Note: This function returns a pointer to a substring of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.
char *trim(char *str) {
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}
