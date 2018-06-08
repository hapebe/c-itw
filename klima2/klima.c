#define DATENBANK "daten.txt"

#include "ausgelagert\\allgemein.c"
#include "ausgelagert\\einAusgaben.c"
#include "ausgelagert\\myfunctions.c"
#include "ausgelagert\\sFunktionen.c"
#include "ausgelagert\\dateiFunktionen.c"

int main(void)
{
	int i,nummer=0;
	struct modell geraet;
	char auswahl;
	while((auswahl=menue())!='x')
	{
		switch(auswahl)
		{
			case '1':	
				system("cls");
				gotoxy(20,0);
				printf("Produkt eingeben");
				printf("\nBezeichnung: ");
				strcpy(geraet.bezeichnung,eingabeBezeichnung());
				printf("\nK\204lteleistung(Watt): ");
				geraet.kleistung=(int)eDouble(4,0);
				printf("\nVerbrauch(Watt): ");
				geraet.verbrauch=(int)eDouble(4,0);
				printf("\nAbmessungen in mm");
				printf("\n=================");
				printf("\nH\224he: ");
				geraet.hoehe=(int)eDouble(5,0);
				printf("\nBreite: ");
				geraet.breite=(int)eDouble(5,0);
				printf("\nTiefe: ");
				geraet.tiefe=(int)eDouble(5,0);
				printf("\nPreis: ");
				geraet.preis=eDouble(4,2);
				
				speichern(&geraet);
				break;
			case '2': 
				laden(&geraet);
				// ausgabe(&geraet);
				break;
		case '3': // loeschen(geraet);
						break;
		case '4': // ersetzen(geraet);
						break;
		case '5': sMenue();
						break;
		}
	}
	return 0;
}



