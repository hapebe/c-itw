#include <stdio.h>
#include "lib/texteingabe.c"

int main(void)
{
	// Die Linux-Version unterstützt Eingaben (zumindest mit
	// Backspace-Support) nur vom Zeilenanfang aus, deshalb mit "\n"
	printf("Eingabe: \n");
	char * buffer = texteingabe();

	printf("Das Ergebnis Ihrer Eingabe: %s\n", buffer);

	// ...aber was hat es nun mit dem Buffer auf sich?
	printf("\nInhalt von buffer: 0x%x\n", buffer);
	printf("&buffer: 0x%x\n", &buffer);
	printf("*buffer: 0x%x\n", *buffer);

	return 0;
}
