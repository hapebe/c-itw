#include <iostream>

using namespace std;

class Stromkreis {
	private:
		double I; // Stromstärke
		double l; // Leitungslänge (einfacher Weg!)
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
				this->rho = 0.07; // Ohm * mm^2 / m
			} else if (material.compare("Konstantan")==0) {
				this->rho = 0.5; // Ohm * mm^2 / m
			} else if (material.compare("Meerwasser")==0) {
				this->rho = 5e+5; // Ohm * mm^2 / m
			} else {
				cout << material << " ist ein unbekanntes Material." << endl;
				exit(1);
			}
			I = 1.0; // A
			l = 100; // m
			A = 2.5; // mm^2
		}
		void setI(double I) { this->I = I; };
		void setL(double l) { this->l = l; };
		void setRho(double rho) { this->rho = rho; };
		void setA(double A) { this->A = A; };
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
			// die *2 ist für reale Leitungen, die 2 Adern haben!
			return rho * l / A * 2;
		}
		
		void statusAusgeben(void) {
			cout << "Stromkreis: I=" << I << "A, ";
			cout << "l=" << l << "m, ";
			cout << "A=" << A << "mm², ";
			cout << "rho=" << rho << "Ohm*mm^2";
			cout << endl;
		}
	
};

int main() {
	Stromkreis s("Kupfer");
	// Rho ist damit gesetzt!
	s.setI(4.7);
	s.setL(134);
	s.setA(2.5);
	
	s.statusAusgeben();
	cout << "Leitungswiderstand: " << s.getLeitungsWiderstand() << "Ohm" << endl;
	cout << "Spannungsabfall: " << s.getSpannungsAbfall() << "V" << endl;
	
    return 0;
}
