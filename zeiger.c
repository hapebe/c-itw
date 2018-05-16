#include <stdio.h>

int main(int argc, char** argv) {
	int a = 10;
	printf("a=%d, Speicherbedarf %ld Bytes, Adresse: %p.\n", a, sizeof a, &a);

	int c = 20;

	int * b = &a;
	printf("b=%p, Speicherbedarf %ld Bytes, b dereferenziert: %d, Adresse: %p.\n", b, sizeof b, *b, &b);

	*b = 30;
	printf("Nach *b = 30:\n");
	printf("a=%d, b dereferenziert=%d.\n", a, *b);

	b++;
	printf("Nach b++:\n");
	printf("b=%p, Speicherbedarf %ld Bytes, b dereferenziert: %d, Adresse: %p.\n", b, sizeof b, *b, &b);

	printf("c=%d\n", c);

	printf("\n====================\n\n");

	char zeichen[]="zum Test";
	char * ptrZeichen = &zeichen[0];
	printf("Zeichen: %c an %p\n", *ptrZeichen, ptrZeichen);
	ptrZeichen += 5;
	printf("Zeichen: %c an %p\n", *ptrZeichen, ptrZeichen);

	printf("\n====================\n\n");

	int zahlen[] = {25,66,77,101,98,88};
	int * ptrZahl = &zahlen[0];
	printf("Zahl: %d an %p\n", *ptrZahl, ptrZahl);
	ptrZahl ++; // nächsten int im Array...
	(*ptrZahl)++; // dereferenzieren, Wert erhöhen.
	printf("Zahl: %d an %p\n", *ptrZahl, ptrZahl);

	return 0;
}
