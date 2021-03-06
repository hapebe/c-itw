// zum Abschalten des Debug-Modus die n�chste Zeile bitte komplett auskommentieren!
// #define DEBUG 1

#include <iostream>
#include <iomanip>
#include <regex>

using namespace std;

class Stromkreis {
	private:
		string material;
		double I; // Stromst�rke
		double l; // Leitungsl�nge (einfacher Weg!)
		double rho; // spezifischer Widerstand
		double A; // Leitungsquerschnitt
		
	public:
		Stromkreis(string material) {
			if (material.compare("Kupfer")==0) {
				// this->rho = 0.0172; // Ohm * mm^2 / m
				this->rho = 0.0178; // Ohm * mm^2 / m
			} else if (material.compare("Silber")==0) {
				this->rho = 0.01587; // Ohm * mm^2 / m
			} else if (material.compare("Aluminium")==0) {
				this->rho = 0.0265; // Ohm * mm^2 / m
			} else if (material.compare("Messing")==0) {
				this->rho = 7e-2; // Ohm * mm^2 / m  (e steht f�r "* 10 ^ ...")
			} else if (material.compare("Konstantan")==0) {
				this->rho = 0.5; // Ohm * mm^2 / m
			} else if (material.compare("Meerwasser")==0) {
				this->rho = 5e+5; // Ohm * mm^2 / m
			} else {
				cout << material << " ist ein unbekanntes Material." << endl;
				exit(1);
			}
			this->material = material;
			
			// Default-Werte f�r die numerischen Angaben:
			I = 1.0; // A
			l = 100; // m
			A = 2.5; // mm^2
		}
		void setI(double I) { this->I = I; };
		void setL(double l) { this->l = l; };
		void setRho(double rho) { this->rho = rho; };
		void setA(double A) { this->A = A; };
		string getMaterial(void) { return material; }
		double getI(void) { return I; }
		double getL(void) { return l; }
		double getRho(void) { return rho; }
		double getA(void) { return A; }
		double getSpannungsAbfall() {
			 // U = I * R
			 return I * getLeitungsWiderstand();
		}
		double getLeitungsWiderstand() {
			// R = rho * l / A
			// das *2 ist f�r reale Leitungen, die 2 Adern haben!
			return rho * l / A * 2;
		}
		
		void statusAusgeben(void) {
			cout << "Stromkreis: Material ist " << material << ", ";
			cout << "rho=" << rho << "Ohm*mm^2, ";
			cout << "l=" << l << "m, ";
			cout << "A=" << A << "mm^2, ";
			cout << "I=" << I << "A";
			cout << endl;
		}
	
};

bool istGueltigeZahl(string s) {
	// der regul�re Ausdruck setzt sich aus folgenden Teilen zusammen:
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
	cout << "Leitungswiderstand: " << s.getLeitungsWiderstand() << "Ohm" << endl;
	cout << "Spannungsabfall: " << s.getSpannungsAbfall() << "V" << endl;
	cout << "Verlustleistung: " << (s.getSpannungsAbfall()* s.getI()) << "W" << endl;
	
    return 0;
}
