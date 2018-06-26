#include <iostream>

using namespace std;

class Flugzeug {
	private:
		bool gestartet;
		bool gelandet;
	public:
		void setGestartet(bool x) { gestartet = x; gelandet = !x; }
		bool getGestartet(void) { return gestartet; }
		void setGelandet(bool x) { gelandet = x; gestartet = !x; }
		bool getGelandet(void) { return gelandet; }
		void starten(void) { gestartet = true; gelandet = false; }
		void landen(void) { gestartet = false; gelandet = true; }
		void zustandAendern(void) { gestartet = !gestartet; gelandet = !gelandet; }
		Flugzeug(bool gestartet, bool gelandet) { this->gestartet = gestartet; this->gelandet = gelandet; }
		// const string toString(void) { return "Flugzeug, " + (gestartet?"gestartet":"gelandet"); }
		friend ostream& operator<<(ostream& os, const Flugzeug& x);
};

ostream& operator<<(ostream& os, Flugzeug const & f) {
	os << "Flugzeug, " << (f.gestartet?"gestartet":"gelandet");
    return os;
}

int main(void) {
	Flugzeug f(false, true);

	cout << f << endl;

	cout << "Starten: ";
	f.starten();
	cout << f << endl;

	cout << "Landen: ";
	f.landen();
	cout << f << endl;

	cout << "Zustand ändern: ";
	f.zustandAendern();
	cout << f << endl;

	cout << "Zustand ändern: ";
	f.zustandAendern();
	cout << f << endl;

	return 0;
}
