#include <iostream>
#include <sstream>

using namespace std;

class Flugzeug {
	protected:
		bool gestartet;
		bool gelandet;
		int hoehe;
	public:
		void setGestartet(bool x) { gestartet = x; gelandet = !x; }
		bool getGestartet(void) { return gestartet; }
		void setGelandet(bool x) { gelandet = x; gestartet = !x; }
		bool getGelandet(void) { return gelandet; }
		int getHoehe(void) { return hoehe; }
		void steigen(void);
		void sinken(void);
		void starten(void) { gestartet = true; gelandet = false; }
		void landen(void) { hoehe=0; gestartet = false; gelandet = true; }
		void zustandAendern(void);
		Flugzeug(bool gestartet = false, bool gelandet = true) {
			this->gestartet = gestartet;
			this->gelandet = gelandet;
			this->hoehe = 0;
		}
		~Flugzeug() {}
		// const string toString(void) { return "Flugzeug, " + (gestartet?"gestartet":"gelandet"); }
		friend ostream& operator<<(ostream& os, const Flugzeug& x);
};

class Segelflugzeug : public Flugzeug {
	protected:
		string bezeichnung;
		int geschwindigkeit;
		static size_t instanzen;
	public:
		Segelflugzeug(int geschwindigkeit = 150) {
			instanzen++;

			stringstream s;
			s << "Segelflugzeug #" << instanzen;
			this->bezeichnung = s.str();
			this->geschwindigkeit = geschwindigkeit;
		}
		~Segelflugzeug(void) { instanzen--; }
		void steigen(void);
		string getBezeichnung(void) { return bezeichnung; }
		void setBezeichnung(string bezeichnung) { this->bezeichnung = bezeichnung; }
		int getGeschwindigkeit(void) { return geschwindigkeit; }
		void setGeschwindigkeit(int v) { geschwindigkeit = v; }
		friend ostream& operator<<(ostream&, const Segelflugzeug&);
};
size_t Segelflugzeug::instanzen=0;


ostream& operator<<(ostream& os, Flugzeug const & f) {
	os << "Flugzeug, " << (f.gestartet?"gestartet":"gelandet");
	if (f.gestartet) os << ", Höhe " << f.hoehe;
    return os;
}

ostream& operator<<(ostream& os, Segelflugzeug const & f) {
	os << f.bezeichnung << ", " << (f.gestartet?"gestartet":"gelandet");
	if (f.gestartet) os << ", Höhe " << f.hoehe;
    return os;
}


void Flugzeug::zustandAendern() {
	// der Flugzustand kann sich nur bei Höhe 0 frei ändern:
	if (hoehe == 0) {
		gestartet = !gestartet;
		gelandet = !gelandet;
	} else {
		throw runtime_error("Das Flugzeug ist nicht am Boden und kann also nicht einfach landen.");
	}
}

void Flugzeug::steigen() {
	if (gestartet) {
		hoehe += 10;
	} else {
		throw runtime_error("Das Flugzeug ist nicht gestartet und kann nicht an Höhe gewinnen.");
	}
}

void Segelflugzeug::steigen() {
	throw runtime_error("Sorry, dieses Segelflugzeug kann generell nicht eigenständig steigen. (Ja, ja, Thermik und so - hier nicht!)");
}


void Flugzeug::sinken() {
	hoehe -= 10;
	if (hoehe < 0) hoehe = 0;
}

int main(void) {
	// Flugzeug f;
	Segelflugzeug f;

	cout << f << endl;

	cout << "Steigen: ";
	try {
		f.steigen();
	} catch (runtime_error ex) {
		cout << "Fehler: " << ex.what() << endl;
	}
	cout << f << endl;

	cout << "Starten: ";
	f.starten();
	cout << f << endl;

	cout << "Steigen: ";
	try {
		f.steigen();
	} catch (runtime_error ex) { cout << "Fehler: " << ex.what() << endl; }
	cout << f << endl;

	cout << "Landen: ";
	f.landen();
	cout << f << endl;

	cout << "Zustand ändern: ";
	try {
		f.zustandAendern();
	} catch (runtime_error ex) {
		cout << "Fehler: " << ex.what() << endl;
	}
	cout << f << endl;

	cout << "Zustand ändern: ";
	try {
		f.zustandAendern();
	} catch (runtime_error ex) {
		cout << "Fehler: " << ex.what() << endl;
	}
	cout << f << endl;

	return 0;
}
