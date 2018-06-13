#include <iostream>

using namespace std;

int addiere(int i0=0, int i1=0, int i2=0, int i3=0) {
	return i0+i1+i2+i3;
}

int main(void) {
	cout << addiere() << endl;
	cout << addiere(1,2,3) << endl;
	
	return 0;
}


