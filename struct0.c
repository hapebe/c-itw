/**
 * Erste Experimente mit struct - dieses Programm kann/soll mit
 * vorgefertigten Eingaben aus der Datei
 *
 * extra/struct0-eingabe
 *
 * getestet werden.
 *
 * ( ./struct0 < extra/struct0-eingabe )
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
// wird nicht gebraucht, wenn ich auf die Funktion
// fliesskommaEingabe(...) verzichte:
// #include "lib/texteingabe.c"

#define N_PERSON 3

struct person {
	char vorname[30];
	char nachname[30];
	int alter;
};

char *trim(char *str);
void scanPerson(struct person * p);
void printPerson(struct person * p);

int main(int argc, char** argv) {
	struct person mensch[N_PERSON];
	// size_t s = sizeof mensch;
	// printf("Speicherbedarf von Mensch: %ld\n", s);

	// mensch[0].alter = 100;
	// strcpy(mensch[0].vorname, "Chadi");

	//int idx;
	//do {
		//printf("Welche Person wollen Sie eingeben (0..9)?\n");
		//idx = fliesskommaEingabe(2,0);
		//scanPerson(&mensch[idx]);
	//} while (idx < 0 || idx > 9);


	int i=0;
	for (i=0; i<N_PERSON; i++) {
		printf("Bitte geben Sie die %d. Person ein!\n", i+1);
		scanPerson(&mensch[i]);
	}

	printf("\nDas sind Ihre Personen:\n");
	for (i=0; i<N_PERSON; i++) {
		printf("%d. ", (i+1));
		printPerson(&mensch[i]);
	}

	return 0;
}

void scanPerson(struct person * p) {
	char puffer[256];
	char* ptrPuffer = &puffer[0];
	char* trimmed;

	printf("Vorname :\n");
	fgets(puffer, 30, stdin);
	trimmed = trim(puffer);
	strcpy((*p).vorname, trimmed); // Syntax 1 für Zeiger-Verweis auf Struktur-Element

	printf("Nachname :\n");
	fgets(puffer, 30, stdin);
	trimmed = trim(puffer);
	strcpy(p->nachname, trimmed); // Syntax 2 für Zeiger-Verweis auf Struktur-Element

	printf("Alter :\n");
	// auskommentiert und ersetzt, weil ich mit getch() keine
	// Eingabe-Umlenkung zum Testen benutzen kann:
	// p->alter = fliesskommaEingabe(3,0);
	fgets(ptrPuffer, 15, stdin);
	trimmed = trim(ptrPuffer);
	p->alter = atoi(trimmed);

}

void printPerson(struct person * p) {
	printf("Vorname: %s, Nachname: %s, Alter: %d\n", p->vorname, p->nachname, p->alter);
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
