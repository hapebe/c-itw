#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX 100
#define BEZEICHNUNG_MAX_L 30

struct modell
{
	char bezeichnung[BEZEICHNUNG_MAX_L + 1];
	int kleistung;
	int verbrauch;
	int hoehe;
	int breite;
	int tiefe;
	double preis;
};

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

char antwort(void)
{
	char temp;
	while(1)
	{
		temp=getch();
		if(temp=='j' || temp=='J')return('J');
		if(temp=='n' || temp=='J')return('N');
	}
}

char menue(void)
{
		char eingabe;
		system("cls");
		gotoxy(19,1);
		printf("Klimager\204te");
		gotoxy(15,3);
		printf("1.) Eingabe");
		gotoxy(15,5);
		printf("2.) Ausgabe");
		gotoxy(15,7);
		printf("3.) L\224schen");
		gotoxy(15,9);
		printf("4.) Ersetzen");
		gotoxy(15,11);
		printf("5.) Suchen");
		gotoxy(15,13);
		printf("x.) Ende");
		gotoxy(15,20);
		printf("Ihre Auswahl: ");
		do
		{
			eingabe=getch();
		}while(!(eingabe>='1' && eingabe<='5') && eingabe!='x');
		return(eingabe);
};

