// zum Abschalten des Debug-Modus die nächste Zeile bitte komplett auskommentieren!
// #define DEBUG 1

#include <iostream>
#include <iomanip>
#include <regex>
#include "physik.cpp"

using namespace std;

class Stromkreis {
	private:
		string material;
		Strom I; // Stromstärke
		Strecke l; // Leitungslänge (einfacher Weg!)
		SpezifischerWiderstand rho; // spezifischer Widerstand
		Flaeche A; // Leitungsquerschnitt
		
	public:
		Stromkreis(string material) {
			if (material.compare("Kupfer")==0) {
				// this->rho = 0.0172; // Ohm * mm^2 / m
				this->rho.set(0.0178); // Ohm * mm^2 / m
			} else if (material.compare("Silber")==0) {
				this->rho.set(0.01587); // Ohm * mm^2 / m
			} else if (material.compare("Aluminium")==0) {
				this->rho.set(0.0265); // Ohm * mm^2 / m
			} else if (material.compare("Messing")==0) {
				this->rho.set(7e-2); // Ohm * mm^2 / m  (e steht für "* 10 ^ ...")
			} else if (material.compare("Konstantan")==0) {
				this->rho.set(0.5); // Ohm * mm^2 / m
			} else if (material.compare("Meerwasser")==0) {
				this->rho.set(5e+5); // Ohm * mm^2 / m
			} else {
				cout << material << " ist ein unbekanntes Material." << endl;
				exit(1);
			}
			this->material = material;
			
			// Default-Werte für die numerischen Angaben:
			I = 1.0; // A
			l = 100; // m
			A = 2.5; // mm^2
		}
		void setI(double I) { this->I.set(I); };
		void setL(double l) { this->l.set(l); };
		void setRho(double rho) { this->rho.set(rho); };
		void setA(double A) { this->A.set(A); };
		string getMaterial(void) { return material; }
		Strom getI(void) { return I; }
		Strecke getL(void) { return l; }
		SpezifischerWiderstand getRho(void) { return rho; }
		Flaeche getA(void) { return A; }
		Spannung getSpannungsAbfall() {
			 // U = I * R
			 return I * getLeitungsWiderstand();
		}
		Widerstand getLeitungsWiderstand() {
			// R = rho * l / A
			// das *2 ist für reale Leitungen, die 2 Adern haben!
			return rho / A * l * 2;
		}
		
		void statusAusgeben(void) {
			cout << "Stromkreis: Material ist " << material << ", ";
			cout << "rho=" << rho << ", ";
			cout << "l=" << l << ", ";
			cout << "A=" << A << ", ";
			cout << "I=" << I;
			cout << endl;
		}
	
};

bool istGueltigeZahl(string s) {
	// der reguläre Ausdruck setzt sich aus folgenden Teilen zusammen:
	// 1. "-" als Vorzeichen, oder nicht
	// 2. entweder eine einzelne Null
	//    ODER eine 1..9 gefolgt von beliebig vielen 0..9
	// 3. entweder nichts, ODER ein Muster wie folgt:
	//    3a. ein "," oder ein "."
	//    3b. beliebig viele 0..9
    regex regexp("-?(0|([1-9][0-9]*))([,\\.][0-9]*)?");
    return regex_match(s, regexp);
}

double fliessKommaEingabe(void) {
	string eingabe;
	bool okay = false;
	while (!okay) {
		cin >> eingabe;
		
		if (istGueltigeZahl(eingabe)) {
			// ggf. vorhandenes "," in einen "." umwandeln, damit stod funktioniert:
			int kommaPos = eingabe.find_first_of(",");
			if (kommaPos != string::npos) {
				eingabe.replace(kommaPos, 1, ".");
			}
			
			return stod(eingabe);
		} else {
			cout << endl;
			cout << "\"" << eingabe << "\" ist keine gueltige Zahl." << endl;
			cout << "Bitte wiederholen Sie die Eingabe: ";
		}
	}
}

int main() {
	cout << "Berechnung des Spannungsabfalls an einer Zuleitung." << endl;
	cout << "Gegeben ist neben den Eigenschaften der Zuleitung eine konstante Stromstaerke." << endl;
	cout << "Es wird die Laenge eines 2-adrigen Kabels erwartet - die wirksame Laenge der Leiter ist also das Doppelte der eingegebenen Laenge!" << endl;
	cout << endl;
	
#ifdef DEBUG
	cout << "Bitte geben Sie eine Kommazahl ein: ";
	double d = fliessKommaEingabe();
	cout << "Eingabe fertig: " << setprecision(12) << d << endl;
	exit(0);
#endif

	cout << "Bitte geben Sie das Leitungsmaterial ein (im Zweifelsfall \"Kupfer\"): ";
	string material;
	getline(cin, material);
	if (material.length() == 0) material = "Kupfer";
	Stromkreis s(material);
	// Rho ist damit gesetzt!
	
	cout << "Bitte geben Sie die Stromstaerke in Ampere ein: ";
	s.setI(fliessKommaEingabe());
	
	cout << "Bitte geben Sie die Laenge der Leitung in Metern ein: ";
	s.setL(fliessKommaEingabe());
	
	cout << "Bitte geben Sie den Leitungsquerschnitt in Quadratmillimetern ein: ";
	s.setA(fliessKommaEingabe());
	
	cout << endl;
	cout << "Wir haben also den folgenden Fall:" << endl;
	s.statusAusgeben();
	
	cout << "Es ergeben sich die folgenden Werte:" << endl;
	cout << "Leitungswiderstand: " << s.getLeitungsWiderstand() << endl;
	cout << "Spannungsabfall: " << s.getSpannungsAbfall() << endl;
	cout << "Verlustleistung: " << (s.getSpannungsAbfall()* s.getI()) << endl;
	
    return 0;
}
