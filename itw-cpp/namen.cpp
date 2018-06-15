using namespace std;

class name {
	private: 
	int var;
	
	public:
	void setVar(int value) { var = value; }
	int getVar(void) { return var; }
};

void namen(void) {
	name x; // das erstellt offenbar direkt eine Instanz!
	
	x.setVar(17);
	cout << "Name x: var ist " << x.getVar() << "." << endl;
}
