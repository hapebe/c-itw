#include <stdio.h>

#define MIN(A,B) (A<B?A:B)
#define MIN3(A,B,C) MIN(MIN(A,B),C)

int minimum(int, int);

int main(int argc, char* argv[]) {
	int a = 207, b = 10, c = 123;
	printf("Das Minimum von %d und %d ist %d.\n", a, b, minimum(a,b));
	printf("Mittels Makro: Das Minimum von %d und %d ist %d.\n", a, b, MIN(a,b));
	printf("Mittels Makro: Das Minimum von %d, %d und %d ist %d.\n", a, b, c, MIN3(a,b,c));
	return 0;
}

int minimum(int a, int b) {
	return (a<b)?a:b;
}
