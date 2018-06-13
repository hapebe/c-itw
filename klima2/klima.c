#define DATENBANK "daten.txt"

#include "ausgelagert\\allgemein.c"
#include "ausgelagert\\einAusgaben.c"
#include "ausgelagert\\sFunktionen.c"
#include "ausgelagert\\dateiFunktionen.c"

int main(void)
{
	struct modell geraet;
	char auswahl;
	
	while((auswahl=menue())!='x')
	{
		switch(auswahl)
		{
			case '1':	
				system("cls");
				gotoxy(20,0);
				printf("Produkt eingeben\n");
				eingabe(&geraet);
				speichern(&geraet);
				break;
			case '2': 
				alleAusgeben(); system("pause"); break;
			case '3': loeschen(); break;
			case '4': ersetzen(); break;
			case '5': sMenue(); break;
		}
	}
	return 0;
}



