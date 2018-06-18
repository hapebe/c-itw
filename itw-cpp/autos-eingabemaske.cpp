#include <windows.h>
#include <stdlib.h>
#ifndef AUTOS
	#include "autos.cpp"
#endif
#define MODUS_STRING 1
#define MODUS_INT 2
#define MODUS_FLOAT 3

enum eAutoFelder { f_hersteller = 0, f_modell, f_verbrauch, f_vmax, f_tankKapazitaet, f_tankinhalt, f_autoMax };

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, coord);
}

/**
 * TODO: negative Zahlen akzeptieren
 */
int istGueltigerIntString(char * s) {
	// leerer String ist okay...
	if (strlen(s)==0) return true;
	
	// führende Null: einzeln okay,
	if (strlen(s) == 1 && s[0] == '0') return true;
	// sonst nicht.
	if (s[0] == '0') return false;
	
	// Haben wir irgendwas, was keine Ziffer ist?
	for (int i=0; i<strlen(s); i++) {
		if (s[i] < '0' || s[i] > '9') return false;
	}
	return true;
}

/**
 * TODO: negative Zahlen akzeptieren
 */
int istGueltigerFloatString(char * s) {
	// leerer String ist okay...
	if (strlen(s)==0) return true;
	
	// führendes Komma ist nicht okay:
	if (s[0] == '.') return false;
	
	// führende Null: einzeln okay,
	if (strlen(s) == 1 && s[0] == '0') return true;
	// sonst nur direkt vor dem Komma:
	if ((s[0] == '0') && (s[1] != '.')) return false;

	// Haben wir mehr als ein Komma?
	int n=0;
	for (int i=0; i<strlen(s); i++) {
		if (s[i] == '.') n++;
	}
	if (n>1) return false;
	
	// Haben wir irgendwas, was keine Ziffer und kein Komma ist?
	for (int i=0; i<strlen(s); i++) {
		if (s[i] < '0' || s[i] > '9') {
			if (s[i] != '.') return false;
		}
	}
	return true;
}

void leereMaskeAnzeigen(void) {
	system("cls");
	gotoxy(5,2); cout << "Auto eingeben";
	
	gotoxy(5,5); cout << "Hersteller:";
	gotoxy(5,6); cout << "____________________";
	
	gotoxy(35,5); cout << "Modell:";
	gotoxy(35,6); cout << "____________________";
	
	gotoxy(5,8); cout << "Verbrauch (l/100km):";
	gotoxy(5,9); cout << "____";
	
	gotoxy(35,8); cout << "V max.:";
	gotoxy(35,9); cout << "___";
	
	gotoxy(5,11); cout << "Tankvolumen:";
	gotoxy(5,12); cout << "___";
	
	gotoxy(35,11); cout << "Tankinhalt:";
	gotoxy(35,12); cout << "______";
}

/**
 * Prüft, ob eines der Datenfelder ungültig ist. Wenn alle Felder gültig sind, wird f_autoMax zurückgegeben.
 */
eAutoFelder ungueltigesFeld(Auto * a) {
	if (a->getHersteller().length() == 0) return f_hersteller;
	if (a->getModell().length() == 0) return f_modell;
	if (a->getVerbrauch() <= 0) return f_verbrauch;
	if (a->getMaxTempo() <= 0) return f_vmax;
	if (a->getTankKapazitaet() <= 0) return f_tankKapazitaet;
	if (a->getTankinhalt() < 0) return f_tankinhalt;
	
	return f_autoMax;
}

void autoInMaskeAnzeigen(Auto * a) {
	// Maske mit aktuellen Werten füllen
	for (int i=0; i<6; i++) {
		switch(i) {
			case f_hersteller:
				gotoxy(5,6); cout << a->getHersteller();
				break;
			case f_modell:
				gotoxy(35,6); cout << a->getModell();
				break;
			case f_verbrauch:
				gotoxy(5,9); cout << a->getVerbrauchFormatted();
				break;
			case f_vmax:
				gotoxy(35,9); cout << a->getMaxTempo();
				break;
			case f_tankKapazitaet:
				gotoxy(5,12); cout << a->getTankKapazitaetFormatted();
				break;
			case f_tankinhalt:
				gotoxy(35,12); cout << a->getTankinhaltFormatted();;
				break;
			default: 
				// NOP
				break;
		}
	}
}

/**
 * modus kann MODUS_STRING, MODUS_INT oder MODUS_FLOAT sein.
 */
int editXY(int x, int y, char * s, int maxLength, int modus) {
	gotoxy(x, y);
	cout << s;
	gotoxy(x+strlen(s), y);

	if (maxLength > 255) {
		fprintf(stderr, "Die Eingabefunktion editXY kann nicht mit String-Längen größer als 255 umgehen.");
		exit(255);
	}
	char buffer[256];
	strcpy(&buffer[0], s);

	int cursor = strlen(&buffer[0]);
	char c;
	
	while (true) { // ganze Bearbeitung
		while (true) { // einzelne Zeicheneingaben auswerten, ggf. gleich verwerfen
			c = getch();
			
			// Steuerzeichen? akzeptieren.
			if (c==9 || c==13 || c==27) break;
			// Backspace nur dann, wenn Zeichen vorhanden sind.
			if (c==8) {
				if (cursor > 0)	break; else continue;
			}
			
			// wenn maximale Länge erreicht, Zeichen ignorieren
			if (cursor >= maxLength) continue;
			
			// String-Modus? alles akzeptieren.
			if (modus == MODUS_STRING) break;
			
			if (modus == MODUS_INT) {
				// akzeptieren, wenn fiktive Eingabe einen gültigen int darstellt:
				buffer[cursor] = c; buffer[cursor+1] = '\0';
				if (istGueltigerIntString(&buffer[0])) break;
				// jedenfalls fiktives Hinzufügen rückgängig machen!
				buffer[cursor] = '\0';
			}
			
			if (modus == MODUS_FLOAT) {
				// akzeptieren, wenn fiktive Eingabe einen gültigen float darstellt:
				buffer[cursor] = c; buffer[cursor+1] = '\0';
				if (istGueltigerFloatString(&buffer[0])) break;
				// jedenfalls fiktives Hinzufügen rückgängig machen!
				buffer[cursor] = '\0';
			}
		}
		// wir haben ein Zeichen Eingabe akzeptiert
		
		// Tab, Return und Escape:
		// Editieren abbrechen, dem Aufrufer melden:
		if (c == 9|| c == 13 || c == 27) {
			strcpy(s, buffer);
			return c;
		}
		
		// Backspace (und ja, wir haben mindestens ein Zeichen!)
		if (c == 8) {
			cout << c << "_" << c;
			buffer[cursor] = '\0';
			cursor--;
			buffer[cursor] = '\0';
			continue;
		}
		
		// ein normales Zeichen:
		buffer[cursor] = c;
		putch(c);
		cursor ++;
		buffer[cursor] = '\0'; // jederzeit ein gültiger C-String
	}
	
	return 0; // <-- wird nie ausgeführt
}

void Auto::mitMaskeEingeben(void) {
	static char temp[256];
	char * buf = &temp[0];
	
	leereMaskeAnzeigen();
	autoInMaskeAnzeigen(this);
	
	eAutoFelder feld = f_hersteller;
	
	while(true) {
		int x, y, maxL, modus;
		switch(feld) {
			case f_hersteller: x=5; y=6; modus=MODUS_STRING; maxL=20; strcpy(buf, this->getHersteller().c_str()); break;
			case f_modell: x=35; y=6; modus=MODUS_STRING; maxL=20; strcpy(buf, this->getModell().c_str()); break;
			case f_verbrauch: x=5; y=9; modus=MODUS_FLOAT; maxL=4; strcpy(buf, this->getVerbrauchFormatted()); break;
			case f_vmax: x=35; y=9; modus=MODUS_INT; maxL=3; sprintf(buf, "%d", this->getMaxTempo()); break;
			case f_tankKapazitaet: x=5; y=12; modus=MODUS_INT; maxL=3; strcpy(buf, this->getTankKapazitaetFormatted()); break;
			case f_tankinhalt: x=35; y=12; modus=MODUS_FLOAT; maxL=5; strcpy(buf, this->getTankinhaltFormatted()); break;
		}
		
		// zur aktuellen Eingabeposition springen,
		// Eingabe-Modus und char[]-Puffer sind vorbereitet:
		int kommando = editXY(x,y,buf,maxL,modus);
		// bei Verlassen (Tab / Return): 
		// 		String-Wert in passendes Feld übernehmen
		// 		nächste (ungültige) Position ansteuern
		
		if (kommando == 27) { // Escape
			break;
		} 
		
		// Wert übernehmen
		switch(feld) {
			case f_hersteller: this->setHersteller(buf); break;
			case f_modell: this->setModell(buf); break;
			case f_verbrauch: this->setVerbrauch(atof(buf)); break;
			case f_vmax: this->setMaxTempo(atoi(buf)); break;
			case f_tankKapazitaet: this->setTankKapazitaet(atof(buf)); break;
			case f_tankinhalt: this->setTankinhalt(atof(buf)); break;
		}
		
		if (kommando == 13) { // Return
			feld = ungueltigesFeld(this);
			if (feld == f_autoMax) break; 
			// ansonsten ist jetzt das ungültige Felder gesetzt
		} else if (kommando == 9) { // Tab
			// ins nächste Feld wechseln:
			int f = (int)feld;
			f = (f+1) % f_autoMax;
			feld = (eAutoFelder)f;
		}
	}
	
	gotoxy(0,20);	
}
