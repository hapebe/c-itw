using namespace std;

class ventilator {
	private:
		string typ;
		int verbrauch;
	public:
		ventilator(void) { 
			typ = "Ventilator"; 
			verbrauch = 0; 
		}
		ventilator(string typ, int verbrauch) {
			this->typ = typ; 
			this->verbrauch = verbrauch; 
		}
		~ventilator(void) {
			cout << "Ventilator " << typ << " mit " << verbrauch << "W wird zerstört." << endl;
		}
		void setTyp(string typ) { this->typ = typ; }
		string getTyp(void) { return this->typ; }
		void setVerbrauch(int verbrauch) { this->verbrauch = verbrauch; }
		int getVerbrauch(void) { return this->verbrauch; }
};

void ventilatoren(void) {
	ventilator tornado("A", 12);
	// tornado.setTyp("Turmventilator");
	// tornado.setVerbrauch(100);
	ventilator * hugo = new ventilator("B", 20);
	
	cout << tornado.getTyp() << " mit " << tornado.getVerbrauch() << "W" << endl;
	cout << hugo->getTyp() << " mit " << hugo->getVerbrauch() << "W" << endl;
	
	delete(hugo);
	// Use-after-free:
	cout << hugo->getTyp() << " mit " << hugo->getVerbrauch() << "W" << endl;
	
	cout << "Letzter Aufruf..." << endl;
}
