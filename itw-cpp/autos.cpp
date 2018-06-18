#include <iomanip>
#include <stdio.h>
#include <string.h>
#include "../lib/string-utils.c"
#ifndef AUTOS
	#define AUTOS 1
#endif

using namespace std;

class Auto {
	private:
		float tankinhalt;
		float tankKapazitaet;
		float verbrauch;
		int maxTempo;
		string hersteller;
		string modell;
		
	public:
		void init();
		
		void setTankinhalt(float tankinhalt) { this->tankinhalt = tankinhalt; }
		void setTankKapazitaet(float tankKapazitaet) { this->tankKapazitaet = tankKapazitaet; }
		void setVerbrauch(float verbrauch) { this->verbrauch = verbrauch; }
		void setMaxTempo(int maxTempo) { this->maxTempo = maxTempo; }
		void setHersteller(string hersteller) { this->hersteller = hersteller; }
		void setModell(string modell) { this->modell = modell; }
		inline float getTankinhalt() { return this->tankinhalt; }
		char * getTankinhaltFormatted() { static char buf[8]; sprintf(&buf[0], "%.1f", this->tankinhalt); return &buf[0]; }
		inline float getTankKapazitaet() { return this->tankKapazitaet; }
		char * getTankKapazitaetFormatted() { static char buf[8]; sprintf(&buf[0], "%.0f", this->tankKapazitaet); return &buf[0]; }
		inline float getVerbrauch() { return this->verbrauch; }
		char * getVerbrauchFormatted() { static char buf[8]; sprintf(&buf[0], "%.1f", this->verbrauch); return &buf[0]; }
		inline int getMaxTempo() { return this->maxTempo; }
		inline string getHersteller() { return this->hersteller; }
		inline string getModell() { return this->modell; }
		
		void interaktivEingeben(void);
		void mitMaskeEingeben(void);
		void ausgeben(void);
		void tabellenZeileAusgeben(void);
		
		float tanken(float menge);
		
		static void tabelleAusgeben(Auto *, int);
		static void tabellenKopfAusgeben(void);
		static void tabellenLinieAusgeben(void);
};

void Auto::init() {
	this->tankinhalt = 0;
	this->tankKapazitaet = 45;
	this->verbrauch = 0;
	this->maxTempo = 0;
	this->hersteller = "unbekannt";
	this->modell = "unbekannt";
}

void Auto::interaktivEingeben() {
	cout << "Hersteller: ";
	getline(cin, this->hersteller);
	cout << "Modell: ";
	getline(cin, this->modell);
	cout << "Höchstgeschwindigkeit: (km/h) ";
	cin >> this->maxTempo;
	cout << "Tankkapazität: (l) ";
	cin >> tankKapazitaet;
	cout << "Tankinhalt: (l) ";
	cin >> tankinhalt;
	cout << "Verbrauch: (l/100km) ";
	cin >> verbrauch;
}

void Auto::ausgeben() {
	cout << fixed << setprecision(1);
	cout << "Hersteller:            " << this->hersteller << endl;
	cout << "Modell:                " << this->modell << endl;
	cout << "Höchstgeschwindigkeit: " << this->maxTempo << "km/h" << endl;
	cout << "Verbrauch:             " << this->verbrauch << "l/100km" << endl;
	if (tankKapazitaet - tankinhalt > 1e-6) {
		cout << setprecision(1);
		cout << "Tankinhalt:            " << this->tankinhalt << "l von max. " << this->tankKapazitaet << "l" << endl;
		cout << setprecision(0);
		cout << "Reichweite:            " << this->tankinhalt / this->verbrauch * 100 << "km";
		cout << " von max. " << this->tankKapazitaet / this->verbrauch * 100 << "km" << endl;
	} else {
		cout << setprecision(1);
		cout << "Tankinhalt:            " << this->tankinhalt << "l (vollgetankt)" << endl;
		cout << setprecision(0);
		cout << "Reichweite:            " << this->tankinhalt / this->verbrauch * 100 << "km" << endl;
	}
}

float Auto::tanken(float menge) {
	if (menge <= 0) return 0;
	
	float tatsaechlicheMenge = 0;
	
	if (this->tankinhalt + menge <= this->tankKapazitaet) {
		tatsaechlicheMenge = menge;
	} else {
		tatsaechlicheMenge = this->tankKapazitaet - this->tankinhalt;
	}
	this->tankinhalt += tatsaechlicheMenge;
	return tatsaechlicheMenge;
}

void Auto::tabelleAusgeben(Auto * autos, int n) {
	Auto::tabellenKopfAusgeben();
	Auto::tabellenLinieAusgeben();
	
	for (int i=0; i<n; i++) {
		Auto * a = autos+i;
		a->tabellenZeileAusgeben();
	}
	
	Auto::tabellenLinieAusgeben();
}

void Auto::tabellenKopfAusgeben() {
	cout << setfill(' ');
	cout << left << setw(12) << "Hersteller" << "| "; // 0 + 14
	cout << left << setw(16) << "Modell" << "| "; // 14 + 16
	cout << left << setw(5) << "Vmax" << "| "; // 30 + 7
	cout << left << setw(8) << "l/100km" << "| "; // 37 + 10
	cout << left << setw(6) << "Sprit" << "| "; // 47 + 8
	cout << left << setw(6) << "T max" << "| "; // 55 + 8
	cout << endl;
}

void Auto::tabellenLinieAusgeben() {
	cout << setw(12) << setfill('-') << "-" << "|-"; // 0 + 14
	cout << setw(16) << setfill('-') << "-" << "|-"; // 14 + 16
	cout << setw(5) << setfill('-') << "-" << "|-"; // 30 + 7
	cout << setw(8) << setfill('-') << "-" << "|-"; // 37 + 10
	cout << setw(6) << setfill('-') << "-" << "|-"; // 47 + 8
	cout << setw(6) << setfill('-') << "-" << "|-"; // 55 + 8
	cout << endl;

	cout << setfill(' ');
}

void Auto::tabellenZeileAusgeben() {
	char puffer[256];
	char * pPuffer = &puffer[0];
	char origPuffer[256];
	char * pOrigPuffer = &origPuffer[0];
	
	
	cout << setfill(' ');

	strcpy(pOrigPuffer, this->hersteller.c_str());
	kuerzen(pPuffer, pOrigPuffer, 11);
	cout << left << setw(12) << pPuffer << "| "; // 0 + 14

	strcpy(pOrigPuffer, this->modell.c_str());
	kuerzen(pPuffer, pOrigPuffer, 15);
	cout << left << setw(16) << pPuffer << "| "; // 14 + 16
	
	cout << right << setw(5) << this->getMaxTempo() << "| "; // 30 + 7

	sprintf(pPuffer, "%.1f", this->getVerbrauch());
	cout << right << setw(8) << pPuffer << "| "; // 37 + 10

	sprintf(pPuffer, "%.1f", this->getTankinhalt());
	cout << right << setw(6) << pPuffer << "| "; // 47 + 8

	sprintf(pPuffer, "%.1f", this->getTankKapazitaet());
	cout << right << setw(6) << pPuffer << "| "; // 55 + 8
	cout << endl;
}

void interaktivTanken(Auto * a) {
	float menge;
	float maxMenge = a->getTankKapazitaet() - a->getTankinhalt();
	cout << setprecision(2);
	cout << "Wieviel Liter wollen Sie tanken? (max. " << maxMenge << "l) ";
	textEingabeAcceptEmpty = 0;
	menge = fliesskommaEingabeMax(4,2,maxMenge);
	
	menge = a->tanken(menge);
	if (menge > 0) cout << "Danke - Sie haben " << menge << "l getankt." << endl;
}

void autos() {
	Auto a[10];
	
	a[0].init();
	
	a[0].setHersteller("Opel");
	a[0].setModell("Astra");
	a[0].setMaxTempo(180);
	a[0].setTankKapazitaet(48);
	a[0].setVerbrauch(8.2);
	a[0].setTankinhalt(4.5);

	a[0].mitMaskeEingeben();

	a[1].init();
	a[1].mitMaskeEingeben();
	// a[1].interaktivEingeben();
	
	Auto::tabelleAusgeben(&a[0], 2);
	

	cout << endl << "Auto[0] im Detail:" << endl;
	a[0].ausgeben();
	
	
	// interaktivTanken(&a[0]);
	// a[0].ausgeben();
}
