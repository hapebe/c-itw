#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lib/getch.c"

int main(void)
{

	char operation, kommando;
	int operand1, operand2, ergebnis;
	float ergebnisF;

	printf("Willkommen bei Ihrem umständlichen Taschenrechner!\n");
	do {
		printf("Bitte geben Sie den ersten Operanden ein: ");
		scanf("%i", &operand1);

		int okay = 0;
		do {
			printf("Wählen Sie eine Operation (+ - * /): ");
			do
				operation = getch();
			while (iscntrl(operation)); // ggf. alte Eingaben entfernen

			if (operation == '+') okay = 1;
			if (operation == '-') okay = 1;
			if (operation == '*') okay = 1;
			if (operation == '/') okay = 1;
			if (!okay) printf("\nDas ist keine gültige Operation...\n");
		} while (!okay);
		printf("%c\n", operation);

		do {
			printf("Bitte geben Sie den zweiten Operanden ein: ");
			scanf("%i", &operand2);

			okay = 1; // erstmal davon ausgehen, dass alles okay ist
			if ((operation == '/') && (operand2 == 0)) {
				okay = 0;
				printf("Sie können hier leider nicht durch 0 dividieren.\n");
			}
		} while (!okay);

		// und jetzt berechnen:
		switch(operation) {
			case '+':
				ergebnis = operand1 + operand2;
				ergebnisF = operand1 + operand2;
				break;
			case '-':
				ergebnis = operand1 - operand2;
				ergebnisF = operand1 - operand2;
				break;
			case '*':
				ergebnis = operand1 * operand2;
				ergebnisF = operand1 * operand2;
				break;
			case '/':
				ergebnis = operand1 / operand2;
				ergebnisF = (float)operand1 / (float)operand2;
				break;
			default: ergebnis = -1; // Fehlerfall, sollte niemals eintreten
		}

		printf("Das int-Ergebnis ist %d.\n", ergebnis);
		printf("Das float-Ergebnis ist %e.\n", ergebnisF);
		printf("Das float-Ergebnis im Format %%5.3f ist %5.3f\n", ergebnisF);

		printf("\nBeliebige Taste zum fortsetzen, x für Abbruch...");
		do
			kommando = getch();
		while (iscntrl(kommando));  //
		printf("\n");

		system("clear"); // Bildschirm löschen
	} while (kommando != 'x');

	return 0;
}
