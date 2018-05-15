#include <stdio.h>

float mittelwert(int, int, int);

int main(int argc, char** argv) {
	int a=8;
	int b=2;
	int c=10;
	printf("Der Mittelwert der Zahlen %d, %d und %d ist %.2f\n", a, b, c, mittelwert(a,b,c));
	return 0;
}

float mittelwert(int a, int b, int c) {
	return (float)(a+b+c) / 3;
}
