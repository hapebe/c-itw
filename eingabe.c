#include <stdio.h>
#include <conio.h>

int main(void) 
{
	int zahl1, zahl2;
	
	printf("Bitte geben Sie Zahl A ein: ");
	scanf("%i", &zahl1); // %i requests an integer, %c would request a char
	
	printf("Bitte geben Sie Zahl B ein: ");
	scanf("%i", &zahl2);
	
	int summe = zahl1 + zahl2;
	printf("Die Summe der Zahlen ist %d.\n", summe);
	
	int i;
	for (i=0; i<3; i++)
	{
		summe += zahl2;
		printf("Diese Summe + %d = %d.\n", zahl2, summe);
	}
	
	do {
		printf("Welche Zahl soll dazu addiert werden? (0 für Abbruch) ");
		scanf("%i", &zahl2);
		summe += zahl2;
		printf("Die Summe ist jetzt %d.\n", summe);
	} while (zahl2 != 0);
	
	return 0;
}
