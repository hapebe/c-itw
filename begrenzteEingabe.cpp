#include <iostream>

using namespace std;

string eingabe() {
	char puffer[31];

	cout << "Bitte geben Sie einen Text ein: ";
	cin.getline(puffer, 30);
	cout << endl;
	
	return puffer;
}

int main(void) {
	cout << "Text: " << eingabe() << endl;
	
	return 0;
}

