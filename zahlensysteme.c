/**
 * Dieses Programm setzt (nur) die geforderte Menü-Führung um; die
 * eigentlichen Algorithmen zur Basis-Umrechnung werden aus den
 * vorhergehenden Übungen wiederverwendet - sie sind als Funktionen in
 * lib/baseconv.c implementiert.
 */

#include <stdio.h>
#include <stdlib.h> // für system() und exit()
#include "lib/baseconv.c"
#include "lib/texteingabe.c"

// dieses Array ist so gestaltet, dass seine Index-Werte mit den Werte
// der entsprechenden Menü-Optionen übereinstimmen (siehe
// zeigeSystemListe())
#define SYSTEM_NAMEN (char*[]){"NULL","dezimal","binär","hexadezimal"}

// für technische Fehlermeldungen:
#define die(TEXT) do {printf ("\n\n%s:%d:%s\n", __FILE__, __LINE__, TEXT); exit(255);} while (0);

void cls();

void zeigeBanner(void) {
	cls();

	printf("Willkommen!\n");
	printf("\n");
	printf("Mit diesem Programm können Sie Ganzzahlen von einem Zahlensystem zum \n");
	printf("anderen Umwandeln. Es unterstützt auch negative Zahlen.\n");
	printf("\n");
	printf("Wenn Sie allerdings die Grenzen eines 32-Bit-int-Wertes überschreiten,\n");
	printf("erhalten Sie falsche (vielleicht lustige) Ergebnisse.\n");
	printf("\n");
	printf("(Bitte eine Taste drücken)\n");
	printf("\n");

	textEingabeAcceptEmpty = -1; // hier auch leere Eingabe akzeptieren...
	textEingabeEinZeichenOhneEcho();
}


void zeigeSystemListe() {
	int i;
	for(i=1; i<=3; i++) {
		char* systemName = SYSTEM_NAMEN[i];
		// in die Literale schreiben (um den ersten Buchstaben in
		// Großschrift umzuwandeln) darf ich offenbar nicht...
		// printf("%c - %d\n", systemName[0], systemName[0]);
		// systemName[0] = (char)(systemName[0] - 32); // --> Speicherschutzfehler!
		printf("\t%d\t%s\n", i, systemName);
	}
}

void zeigeEingabeMenu() {
	cls();

	printf("Bitte wählen Sie ein Zahlensystem für die Zahlen-Eingabe:\n\n");
	zeigeSystemListe();
	printf("\n\tx\tAbbruch\n");
}

void zeigeAusgabeMenu() {
	cls();

	printf("Bitte wählen Sie ein Zahlensystem für die Zahlen-Ausgabe:\n\n");
	zeigeSystemListe();
	printf("\n\tx\tAbbruch\n");
}

int main(int argc, char *argv[]) {
	initReverseCharPool(); // das wird für die Funktionen von lib/baseconv.c benötigt...

	zeigeBanner();

	while (-1) {
		// Hauptschleife - kann nur per break; verlassen werden

		// Helfer-Variablen:
		char* erlaubteSymbole;
		char* kommando; // über die Tastatur eingegebene Befehle / Menu-Auswahlen
		int kommandoInt;
		int zahlGueltig = 0;

		// "Payload"-Variablen:
		char* eingabe;
		int zahl;
		int basisInput = -1, basisOutput = -1;

		// Eingabe-Menu:
		zeigeEingabeMenu();
		textEingabeAcceptEmpty = 0; // keine leere Eingabe akzeptieren...
		kommando = textEingabeEinZeichenAusMengeOhneEcho((char[]){'1','2','3','x','X','\0'}); // printf("\n%c", kommando[0]);
		kommandoInt = (int)kommando[0] - 48; // ASCII-Code in Ziffer umwandeln

		int abbruch = 0;
		switch (kommando[0]) {
			case '1':
				basisInput = 10;
				erlaubteSymbole = &(char[]){'-','0','1','2','3','4','5','6','7','8','9','\0'}[0];
				break;
			case '2':
				basisInput = 2;
				erlaubteSymbole = &(char[]){'-','0','1','\0'}[0];
				break;
			case '3':
				basisInput = 16;
				erlaubteSymbole = &(char[]){
					'-',
					'0','1','2','3','4','5','6','7','8','9',
					'a','b','c','d','e','f',
					'A','B','C','D','E','F',
					'\0'
				}[0];
				break;
			case 'x':
			case 'X':
				abbruch = -1;
				break;
			default: die("Unmöglicher Fall beim Eingabe-Menü...");
		}
		if (abbruch) break;


		// Die eigentliche Zahl eingeben:
		cls();
		zahlGueltig = 0;
		while (!zahlGueltig) {
			printf("Bitte geben Sie eine %se Zahl ein:\n", SYSTEM_NAMEN[kommandoInt]);
			textEingabeAcceptEmpty = 0; // keine leere Eingabe akzeptieren...
			eingabe = texteingabeLengthSet(32, erlaubteSymbole); // printf("Eingegebene Zahl: %s", eingabe); break;

			// testen, ob hinter der ersten Stelle ein "-" vorkommt:
			zahlGueltig = -1; int i;
			// wir erzwingen die Eingabe eines nicht-leeren Strings,
			// deshalb darf ich einfach bei Index 1 anfangen:
			for (i=1; eingabe[i]!=0; i++) {
				if (eingabe[i] == '-') zahlGueltig = 0;
			}
			if (!zahlGueltig) printf("Das ist keine gültige Zahl...\n");
		}

		// ...und den entsprechenden int-Wert ermitteln:
		zahl = getNumericIntBase(eingabe, basisInput); // in lib/baseconv.c
			// printf("Zahl: %d\n", zahl); break;


		// Ausgabe-Menu:
		zeigeAusgabeMenu();
		textEingabeAcceptEmpty = 0; // keine leere Eingabe akzeptieren...
		kommando = textEingabeEinZeichenAusMengeOhneEcho((char[]){'1','2','3','x','X','\0'}); // printf("\n%c", kommando[0]);
		kommandoInt = (int)kommando[0] - 48; // ASCII-Code in Ziffer umwandeln

		abbruch = 0;
		switch (kommando[0]) {
			case '1':
				basisOutput = 10;
				break;
			case '2':
				basisOutput = 2;
				break;
			case '3':
				basisOutput = 16;
				break;
			case 'x':
			case 'X':
				abbruch = -1;
				break;
			default: die("Unmöglicher Fall beim Ausgabe-Menü...");
		}
		if (abbruch) break;


		// die Zahl entsprechend ausgeben:
		cls();
		printf(
			"Ihre Zahl sieht %s dann so aus: %s\n",
			SYSTEM_NAMEN[kommandoInt],
			getSymbolicIntBase(zahl, basisOutput) // Funktion aus lib/baseconv.c
		);
		printf("\n\t(x für Abbruch, andere Taste für Fortsetzen...)\n");
		textEingabeAcceptEmpty = -1; // hier auch leere Eingabe akzeptieren...
		kommando = textEingabeEinZeichenOhneEcho(); // printf("\n%c", kommando[0]);

		abbruch = 0;
		switch (kommando[0]) {
			case 'x':
			case 'X':
				abbruch = -1;
			default: ;
		}
		if (abbruch) break;


	} // Ende der Hauptprogramm-Endlosschleife

	return 0;
}

/**
 * löscht den Konsolen-Bildschirm
 * (tricky wegen Unterschieden Windows/Linux)
 */
void cls() {
#ifdef _WIN32
	system("cls");
#endif

#ifdef __linux__
	system("clear");
#endif
}
