#include <stdio.h>

// globale Variable:
char * fname = "/home/user/temp/files1-output.txt";

int dateiLesen();
int dateiSchreiben();

int main(int argc, char** argv) {

	// if (dateiSchreiben() != 0) return 1;

	if (dateiLesen() != 0) return 1;

	return 0;
}

int dateiSchreiben() {
	FILE * f = fopen(fname, "a");
	if (f == NULL) {
		fprintf(stderr, "Die Datei '%s' konnte nicht zum Schreiben geöffnet werden.\n", fname);
		return 1;
	}

	printf("Datei-Handle-Zeiger: %lx\n", (unsigned long int)f);

	//int i=0;
	//for (i=65; i<91; i++) {
	//for (i=90; i>=65; i--) {
		//fputc((char)i, f);
	//}
	//fputc('\n', f);

	// Zeichenweise "kopieren" (in diesem Fall von stdin, also einfach eintippen...)
	char temp;
	do {
		temp = fgetc(stdin);
		fputc(temp, f);
	} while ((temp != 13) && (temp != 10) && (temp != 0));


	fclose(f);
	return 0;
}

int dateiLesen() {
	FILE * f = fopen(fname, "r");
	if (f == NULL) {
		fprintf(stderr, "Die Datei '%s' konnte nicht zum Lesen geöffnet werden.\n", fname);
		return 1;
	}

	printf("Datei-Handle-Zeiger: %lx\n", (unsigned long int)f);

	char temp;
	while(!feof(f)) {
		temp = fgetc(f);
		if (temp != EOF) {
			fputc(temp, stdout);
		} else {
			printf("\n\nEOF: %d\n", temp);
		}
	}

	fclose(f);
	return 0;
}
