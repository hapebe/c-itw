
double eDouble(int vorkomma,int nachkomma) 
{
	double wert=0,faktor2=1;
	int komma=0,zVorkomma=0,zNachkomma=0,j,faktor;
	char eingabe,vArray[16],nArray[6];
	
	do
	{
		do
		{
			eingabe=getch();
		}while(!(eingabe>=48 && eingabe <=57) && eingabe!=8 && eingabe!=13
					&& eingabe!=44 && eingabe!=46);
		if(eingabe!=8 && eingabe!=13) 
		{
			if(komma==0 && zVorkomma<vorkomma && eingabe!=44 && eingabe!=46)
			{	
				vArray[zVorkomma]=eingabe;
				zVorkomma++;			
				putch(eingabe);
			}
			if(komma==1 && zNachkomma<nachkomma && eingabe!=44 && eingabe!=46)
			{	
				nArray[zNachkomma]=eingabe;
				zNachkomma++;			
				putch(eingabe);
			}
			if((eingabe==46 || eingabe==44)&&komma==0&&zVorkomma>0)
			{
				komma=1;
				putch(',');
			}
		}
		if(eingabe==8)
		{
			if(komma==0 && zVorkomma>0)
			{
				putch(eingabe);
				putch(32);	
				putch(eingabe);
				zVorkomma--;	
			}
			if(zNachkomma==0 && komma==1)
			{
				putch(eingabe);
				putch(32);	
				putch(eingabe);
				komma=0;	
			}
			if(komma==1 && zNachkomma>0)
			{
				putch(eingabe);
				putch(32);	
				putch(eingabe);
				zNachkomma--;	
			}

		}
					
	}while((eingabe!=13 &&zVorkomma!=0)||zVorkomma==0);
	
	
	for(j=zVorkomma-1;j>=0;j--)
	{
		if(j==zVorkomma-1)faktor=1;
		else faktor*=10;
		wert+=(vArray[j]-48)*faktor;
	}
	for(j=0;j<zNachkomma;j++)
	{
		faktor2*=0.1;
		wert+=(nArray[j]-48)*faktor2;
	}
	
	return(wert);
};

char *eingabeBezeichnung(void)
{
	char temp;
	static char tempArray[31];
	int i=0;
	do
	{
		do
		{
			temp=getch();
		}while(
			!(temp>=48 && temp<=57) // Ziffern
			&& temp!=32	// Leerzeichen
			&& !(temp>=65 && temp<=90) // Großbuchstaben
			&& !(temp>=97 && temp<=122) // Kleinbuchstaben
			&& temp!=13 // <Return>
			&& temp!=8 // <Backspace>
		);
		if(temp!=8 && temp!=13 && i<30)
		{
			putch(temp);
			tempArray[i]=temp;
			i++;
		}
		if(temp==8 && i>0)
		{
			putch(temp);
			putch(32);
			putch(temp);
			i--;
		}
	}while(temp!=13 || i==0);
	tempArray[i]='\0';
	return(tempArray);
};


void tabellenHeader() {
	printf(" Nr ");
	printf("%30s ","Bezeichnung");
	printf("%10s","K/Watt");
	printf("%10s","V/Watt");
	printf("%20s","Abmessung(H/B/T)");
	printf("  %5s ","Preis");
	printf("\n");
}

void ausgabeZeile(int nr, struct modell *geraet) {
	printf(" %2d ",nr);
	printf("%30s ",geraet->bezeichnung);
	printf("%10d",geraet->kleistung);
	printf("%10d",geraet->verbrauch);
	printf("   %5dx",geraet->hoehe);
	printf("%5dx",geraet->breite);
	printf("%5d ",geraet->tiefe);
	printf(" %7.2f",geraet->preis);
	printf("\n");
}


void eingabe(struct modell *geraet) {
	printf("\nBezeichnung: ");
		strcpy(geraet->bezeichnung,eingabeBezeichnung());
	printf("\nK\204lteleistung(Watt): ");
		geraet->kleistung=(int)eDouble(4,0);
	printf("\nVerbrauch(Watt): ");
		geraet->verbrauch=(int)eDouble(4,0);
	printf("\nAbmessungen in mm");
	printf("\n=================");
	printf("\nH\224he: ");
		geraet->hoehe=(int)eDouble(5,0);
	printf("\nBreite: ");
		geraet->breite=(int)eDouble(5,0);
	printf("\nTiefe: ");
		geraet->tiefe=(int)eDouble(5,0);
	printf("\nPreis: ");
		geraet->preis=eDouble(4,2);
}

