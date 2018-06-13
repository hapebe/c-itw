#include <iostream>
#include <iomanip>

#define MAX 10

using namespace std;
int main(void) {
	int dividenden[MAX];
	int divisoren[MAX];
	
	for (int i=0; i<MAX; i++) {
		cout << "Bitte geben Sie den " << i+1 << ". Dividenden ein: ";
		cin >> dividenden[i];
	}
	for (int i=0; i<MAX; i++) {
		cout << "Bitte geben Sie den " << i+1 << ". Divisoren ein: ";
		cin >> divisoren[i];
	}
	cout << "Danke! Dies sind Ihre Gleichungen: " << endl;
	
	for (int i=0; i<10; i++) {
		cout << setw(12) << setfill(' ') << setiosflags(/* ios::showpos | */ ios::right);
		cout << dividenden[i];
		cout << " / ";
		cout << setw(12) << setfill(' ') << setiosflags(/* ios::showpos | */ ios::right);
		cout << divisoren[i];
		cout << " = ";
		cout << setw(12) << setfill(' ') << setiosflags(/* ios::showpos | */ ios::right);
		cout << setprecision(2) << fixed;
		cout << (double)dividenden[i] / divisoren[i];
		cout << endl;
	}
	cout << resetiosflags(ios::showpos | ios::right) << setfill(' ') << setw(1);
	
	return 0;
}

