#include <iostream>

using namespace std;

int main(void) {
	// das Programm funktioniert nur auf Windows-Rechnern, deren Konsolen 
	// mit der Codepage 737 arbeiten - also deren entsprechende Sprach- / 
	// Regionseinstellung auf "Griechisch" steht
	
	system("chcp"); cout << endl;
	
	// der Rechner PC 14 benutzt laut Auskunft von "chcp" die Codepage 737
	// danach steht der Code A8 fuer das Rho, 168 Dezimal, 250 Oktal
	
	char rho = 168;
	cout << "Rho ((char)168) sieht hier so aus: " << rho << endl;
	cout << "Und als oktale \"Escape-Sequenz\" \\250: \250" << endl;
	cout << endl;
	
	cout << "Das ganze griechische Alphabet (Grossbuchstaben):" << endl;
	for (int i=128; i<=151 ; i++) {
		cout << (char)i;
	}
	cout << endl;
	cout << endl;

	cout << "Das ganze griechische Alphabet (Kleinbuchstaben):" << endl;
	for (int i=152; i<=175 ; i++) {
		cout << (char)i;
	}
	cout << endl;
	cout << endl;
	
	return 0;
}
