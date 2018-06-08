void loeschen(struct modell *ptrLoeschen)
{
	int temp;
	system("cls");
	printf("Geben Sie die Nummer des zu l\224schenden Produkts ein:");
	temp=eDouble(2,0)-1;
	if(temp<MAX && temp>=0)
	{
			if((ptrLoeschen+temp)->bezeichnung[0]=='\0')
			{
				printf("\nProdukt nicht vorhanden\n\n");
				system("pause");
			}
			else
			{	
				printf("\n Nr ");
				printf("%30s ","Bezeichnung");
				printf("%10s","K/Watt");
				printf("%10s","V/Watt");
				printf("%20s","Abmessung(H/B/T)");
				printf("  %5s \n","Preis");
				printf(" %2d ",temp+1);
				printf("%30s ",(ptrLoeschen+temp)->bezeichnung);
				printf("%10d",(ptrLoeschen+temp)->kleistung);
				printf("%10d",(ptrLoeschen+temp)->verbrauch);
				printf("   %5dx",(ptrLoeschen+temp)->hoehe);
				printf("%5dx",(ptrLoeschen+temp)->breite);
				printf("%5d ",(ptrLoeschen+temp)->tiefe);
				printf(" %7.2f\n",(ptrLoeschen+temp)->preis);
				printf("\n\nWollen Sie das Produkt wirklich löschen(J/N):");
				if('J'==antwort())(ptrLoeschen+temp)->bezeichnung[0]='\0';
			}
	
	}
	else
	{
		printf("\n\nEingabe nicht erlaubt\n\n\n");
		system("pause");
	}
};

void ersetzen(struct modell *ptrErsetzen)
{
	int temp;
	system("cls");
	printf("Geben Sie die Nummer des zu ersetzenden Produkts ein:");
	temp=eDouble(2,0)-1;
	if(temp<MAX && temp>=0)
	{
			if((ptrErsetzen+temp)->bezeichnung[0]=='\0')
			{
				
				printf("\n\nNeues Produkt anlegen(J/N)");
			}
			else
			{	
				printf("\n Nr ");
				printf("%30s ","Bezeichnung");
				printf("%10s","K/Watt");
				printf("%10s","V/Watt");
				printf("%20s","Abmessung(H/B/T)");
				printf("  %5s \n","Preis");
				printf(" %2d ",temp+1);
				printf("%30s ",(ptrErsetzen+temp)->bezeichnung);
				printf("%10d",(ptrErsetzen+temp)->kleistung);
				printf("%10d",(ptrErsetzen+temp)->verbrauch);
				printf("   %5dx",(ptrErsetzen+temp)->hoehe);
				printf("%5dx",(ptrErsetzen+temp)->breite);
				printf("%5d ",(ptrErsetzen+temp)->tiefe);
				printf(" %7.2f\n",(ptrErsetzen+temp)->preis);
				printf("\n\nProdukt \201berschreiben(J/N):");
			}
			if(antwort()=='J')
			{
				system("cls");
				printf("Produkt%d eingeben",temp+1);
				printf("\nBezeichnung: ");
				strcpy((ptrErsetzen+temp)->bezeichnung,eingabeBezeichnung());
				printf("\nK\204lteleistung(Watt): ");
				(ptrErsetzen+temp)->kleistung=(int)eDouble(4,0);
				printf("\nVerbrauch(Watt): ");
				(ptrErsetzen+temp)->verbrauch=(int)eDouble(4,0);
				printf("\nAbmessungen in mm");
				printf("\n=================");
				printf("\nH\224he: ");
				(ptrErsetzen+temp)->hoehe=(int)eDouble(5,0);
				printf("\nBreite: ");
				(ptrErsetzen+temp)->breite=(int)eDouble(5,0);
				printf("\nTiefe: ");
				(ptrErsetzen+temp)->tiefe=(int)eDouble(5,0);
				printf("\nPreis: ");
				(ptrErsetzen+temp)->preis=eDouble(4,2);
			}
	
	}
	else
	{
		printf("\n\nEingabe nicht erlaubt");
		system("pause");
	}
};

