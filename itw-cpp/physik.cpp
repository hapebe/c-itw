/**
 * Sinn dieser Klassen-Sammlung ist das Ausprobieren von 
 * überladenen Operatoren - das scheint mir (Hans-Peter) 
 * besonders verlockend, weil *diese* Möglichkeit in meiner 
 * bisherigen Lieblings-Seriösen-Sprache Java nicht besteht!
 */

#include <iostream>
#include <typeinfo> // habe ich von: https://stackoverflow.com/questions/351845/finding-the-type-of-an-object-in-c

using namespace std;

class PhysGroesse {
	protected:
		double wert;
	
	public:
		PhysGroesse(void) { this->wert = 0; }
		double get(void) { return this->wert; }
		void set(double V) { wert = V; }
		
		// const verspricht: es wird nichts an dem Objekt geändert!
		// virtual sorgt dafür, dass ggf. die Methode des abgeleiteten Objekts aufgerufen wird
		const virtual void ausgabe(void) { 
			cout << "Physikalische Groesse";
		}
		// das hier habe ich hier aufgeschnappt:
		// https://msdn.microsoft.com/en-us/library/1z2f6c2k.aspx
		friend ostream& operator<<(ostream& os, const PhysGroesse& x);
};



class Strecke : public PhysGroesse {
	public:
		Strecke() { this->wert = 0; }
		Strecke(double wert) { this->wert = wert; }
		const virtual void ausgabe(void) { cout << "Strecke=" << wert << "m"; }
};

class Flaeche : public PhysGroesse {
	public:
		Flaeche() { this->wert = 0; }
		Flaeche(double wert) { this->wert = wert; }
		const virtual void ausgabe(void) { cout << "Flaeche=" << wert << "mm^2"; }
};

class Spannung : public PhysGroesse {
	public:
		Spannung() { this->wert = 0; }
		Spannung(double wert) { this->wert = wert; }
		const virtual void ausgabe(void) { cout << "Spannung=" << wert << "V"; }
};

class Strom : public PhysGroesse {
	public:
		Strom() { this->wert = 0; }
		Strom(double wert) { this->wert = wert; }
		const virtual void ausgabe(void) { cout << "Strom=" << wert << "A"; }
};

class Widerstand : public PhysGroesse {
	public:
		Widerstand() { this->wert = 0; }
		Widerstand(double wert) { this->wert = wert; }
		const virtual void ausgabe(void) { cout << "Widerstand=" << wert << "Ohm"; }
};

class SpezifischerWiderstand : public PhysGroesse {
	public:
		SpezifischerWiderstand() { this->wert = 0; }
		SpezifischerWiderstand(double wert) { this->wert = wert; }
		const virtual void ausgabe(void) { cout << "spez. Widerstand=" << wert << "Ohm*mm^2/m"; }
};

class WiderstandJeStrecke : public PhysGroesse {
	public:
		WiderstandJeStrecke() { this->wert = 0; }
		WiderstandJeStrecke(double wert) { this->wert = wert; }
		const virtual void ausgabe(void) { cout << "Widerstand je Strecke=" << wert << "Ohm/m"; }
};


class Leistung : public PhysGroesse {
	public:
		Leistung() { this->wert = 0; }
		Leistung(double wert) { this->wert = wert; }
		const virtual void ausgabe(void) { cout << "Leistung=" << wert << "W"; }
};

ostream& operator<<(ostream& os, PhysGroesse const& x) {
	if (typeid(x) == typeid(PhysGroesse)) {
		os << "(PhysGroesse)";
	} else if (typeid(x) == typeid(Strecke)) {
		os << x.get() << "m";
	} else if (typeid(x) == typeid(Flaeche)) {
		os << x.get() << "mm^2";
	} else if (typeid(x) == typeid(Spannung)) {
		os << x.get() << "V";
	} else if (typeid(x) == typeid(Strom)) {
		os << x.get() << "A";
	} else if (typeid(x) == typeid(Leistung)) {
		os << x.get() << "W";
	} else if (typeid(x) == typeid(Widerstand)) {
		os << x.get() << "Ohm";
	} else if (typeid(x) == typeid(SpezifischerWiderstand)) {
		os << x.get() << "Ohm*mm^2/m";
	} else {
		os << "(nicht unterstützte PhysGroesse in << ...)";
	}
    return os;  
}

Leistung operator*(Spannung u, Strom i) {
	return Leistung(u.get() * i.get());
}

Widerstand * operator/(Spannung u, Strom i) {
	return new Widerstand(u.get() / i.get());
}

Widerstand operator*(Widerstand r, double d) {
	return Widerstand(r.get() * d);
}

Spannung operator*(Strom i, Widerstand r) {
	return Spannung(i.get() * r.get());
}

WiderstandJeStrecke operator/(SpezifischerWiderstand rho, Flaeche A) {
	return WiderstandJeStrecke(rho.get() / A.get());
}

Widerstand operator*(WiderstandJeStrecke rProL, Strecke l) {
	return Widerstand(rProL.get() * l.get());
}


/*
int main(void) {
	Spannung u = Spannung(5); // 5 V...
	Strom i = Strom(0.3); // 0,3 A...
	
	u.ausgabe(); cout << endl;
	i.ausgabe(); cout << endl;
	
	Leistung p = u*i;
	cout << "Leistung: " << p << endl;
	
	PhysGroesse * r = u/i;
	cout << "Widerstand: " << *r << endl;
	
	cout << "Spannung: " << u << endl;
	
	return 0;
}
*/
