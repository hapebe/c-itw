#include <stdio.h>

int main(void) {
	int a;
	int *ptrA = &a;
	printf("Adresse von a: %x\n", (long)ptrA);

	ptrA = (int *)140723213994316;
	printf("Wert an %ld: %d\n", (long)ptrA, *ptrA);


	return 0;
}

