
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
		}while(!(temp>=48 && temp<=57)&& temp!=13 && temp!=8 &&
					!(temp>=65 && temp<=90)&&!(temp>=97 && temp<=122));
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

void ausgabe(struct modell *ptrBezeichnung)
{
	int i;
	system("cls");
		printf(" Nr ");
		printf("%30s ","Bezeichnung");
		printf("%10s","K/Watt");
		printf("%10s","V/Watt");
		printf("%20s","Abmessung(H/B/T)");
		printf("  %5s \n","Preis");
	// for(i=0;i<MAX;i++)
	i=0;
	{
		if((ptrBezeichnung+i)->bezeichnung[0]!='\0')
		{
			printf(" %2d ",i+1);
			printf("%30s ",(ptrBezeichnung+i)->bezeichnung);
			printf("%10d",(ptrBezeichnung+i)->kleistung);
			printf("%10d",(ptrBezeichnung+i)->verbrauch);
			printf("   %5dx",(ptrBezeichnung+i)->hoehe);
			printf("%5dx",(ptrBezeichnung+i)->breite);
			printf("%5d ",(ptrBezeichnung+i)->tiefe);
			printf(" %7.2f\n",(ptrBezeichnung+i)->preis);
		}
	}
	printf("\0");
	system("pause");
}

void tabellenHeader() {
		printf(" Nr ");
		printf("%30s ","Bezeichnung");
		printf("%10s","K/Watt");
		printf("%10s","V/Watt");
		printf("%20s","Abmessung(H/B/T)");
		printf("  %5s ","Preis");
		printf("\n");
}


