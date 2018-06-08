void sKaelteleistung() {
	int min,max;
	struct modell buffer; // lokale Variable, reserviert auch den Speicher für eine Struktur
	struct modell * geraet = &buffer;
	
	system("cls");
	printf("Suche K\204lteleistung\n");
	printf("Bitte den Bereich f\201r die Suche eingeben:   ");
	printf("Min: ");
	min=eDouble(4,0); 
	printf("    Max: ");
	max=eDouble(4,0); 

	printf("\nErgebnisse:\n");
	
	FILE * in;
	
	in = fopen(DATENBANK, "r");
	if (in == NULL) {
		fprintf(stderr, "Konnte die Datenbank %s nicht zum Lesen öffnen!\n", DATENBANK);
		system("pause");
		return;
	}
	
	int i=0;
	while (fread(geraet, sizeof(struct modell), 1, in) == 1) {
		if(geraet->bezeichnung[0]!='\0' ) {	
			if (geraet->kleistung>=min && geraet->kleistung <=max) {
				if (i==0) tabellenHeader();
				printf(" %2d ",i+1);
				printf("%30s ",geraet->bezeichnung);
				printf("%10d",geraet->kleistung);
				printf("%10d",geraet->verbrauch);
				printf("   %5dx",geraet->hoehe);
				printf("%5dx",geraet->breite);
				printf("%5d ",geraet->tiefe);
				printf(" %7.2f\n",geraet->preis);
				i ++;
			}
		}
	}
	if (i==0) {
		printf("Leider keine Suchtreffer...\n");
	}
	
	fclose(in);
	system("pause");
};

void sVerbrauch() {
	struct modell buffer; // lokale Variable, reserviert auch den Speicher für eine Struktur
	struct modell * geraet = &buffer;
	int min,max;
	
	system("cls");
	printf("Suche Verbrauch\n");
	printf("Bitte den Bereich f\201r die Suche eingeben:   ");
	printf("Min: ");
	min=eDouble(4,0); 
	printf("    Max: ");
	max=eDouble(4,0); 
	
	printf("\nErgebnisse:\n");
	
	FILE * in;
	
	in = fopen(DATENBANK, "r");
	if (in == NULL) {
		fprintf(stderr, "Konnte die Datenbank %s nicht zum Lesen öffnen!\n", DATENBANK);
		system("pause");
		return;
	}
	
	int i=0;
	while (fread(geraet, sizeof(struct modell), 1, in) == 1) {
		if(geraet->bezeichnung[0]!='\0' ) {	
			if(geraet->verbrauch>=min && geraet->verbrauch<=max) {
				if (i==0) tabellenHeader();
				printf(" %2d ",i+1);
				printf("%30s ",geraet->bezeichnung);
				printf("%10d",geraet->kleistung);
				printf("%10d",geraet->verbrauch);
				printf("   %5dx",geraet->hoehe);
				printf("%5dx",geraet->breite);
				printf("%5d ",geraet->tiefe);
				printf(" %7.2f\n",geraet->preis);
				i ++;
			}
		}
	}
	if (i==0) {
		printf("Leider keine Suchtreffer...\n");
	}
	
	fclose(in);
	system("pause");
};

void sPreis() {
	float min,max;
	struct modell buffer; // lokale Variable, reserviert auch den Speicher für eine Struktur
	struct modell * geraet = &buffer;

	system("cls");
	printf("Suche Preis\n");
	printf("Bitte den Bereich f\201r die Suche eingeben:   ");
	printf("Min: ");
	min=eDouble(4,2); 
	printf("    Max: ");
	max=eDouble(4,2); 

	printf("\nErgebnisse:\n");
	
	FILE * in;
	
	in = fopen(DATENBANK, "r");
	if (in == NULL) {
		fprintf(stderr, "Konnte die Datenbank %s nicht zum Lesen öffnen!\n", DATENBANK);
		system("pause");
		return;
	}
	
	int i=0;
	while (fread(geraet, sizeof(struct modell), 1, in) == 1) {
		if(geraet->bezeichnung[0]!='\0' ) {	
			if (geraet->preis>=min && geraet->preis<=max) {
				if (i==0) tabellenHeader();
				printf(" %2d ",i+1);
				printf("%30s ",geraet->bezeichnung);
				printf("%10d",geraet->kleistung);
				printf("%10d",geraet->verbrauch);
				printf("   %5dx",geraet->hoehe);
				printf("%5dx",geraet->breite);
				printf("%5d ",geraet->tiefe);
				printf(" %7.2f\n",geraet->preis);
				i ++;
			}
		}
	}
	if (i==0) {
		printf("Leider keine Suchtreffer...\n");
	}
	
	fclose(in);
	system("pause");

};

void sAbmessung() {
	struct modell buffer; // lokale Variable, reserviert auch den Speicher für eine Struktur
	struct modell * geraet = &buffer;
	int minHoehe,maxHoehe,minBreite,maxBreite,minTiefe,maxTiefe;
	
	system("cls");
	printf("Suche Abmessungen");
	printf("\nBitte den Bereich f\201r die H\224he eingeben:   ");
	printf("Min: ");
	minHoehe=eDouble(4,0); 
	printf("    Max: ");
	maxHoehe=eDouble(4,0); 
	printf("\nBitte den Bereich f\201r die Breite eingeben:   ");
	printf("Min: ");
	minBreite=eDouble(4,0); 
	printf("    Max: ");
	maxBreite=eDouble(4,0); 
	printf("\nBitte den Bereich f\201r die Tiefe eingeben:   ");
	printf("Min: ");
	minTiefe=eDouble(4,0); 
	printf("    Max: ");
	maxTiefe=eDouble(4,0); 

	printf("\nErgebnisse:\n");
	
	FILE * in;
	
	in = fopen(DATENBANK, "r");
	if (in == NULL) {
		fprintf(stderr, "Konnte die Datenbank %s nicht zum Lesen öffnen!\n", DATENBANK);
		system("pause");
		return;
	}
	
	int i=0;
	while (fread(geraet, sizeof(struct modell), 1, in) == 1) {
		if(geraet->bezeichnung[0]=='\0' ) continue;
		
		if (
			(geraet->hoehe>=minHoehe && geraet->hoehe <=maxHoehe)
			&& (geraet->breite>=minBreite && geraet->breite <=maxBreite)
			&& (geraet->tiefe>=minTiefe && geraet->tiefe <=maxTiefe)	
		) {
			if (i==0) tabellenHeader();
			printf(" %2d ",i+1);
			printf("%30s ",geraet->bezeichnung);
			printf("%10d",geraet->kleistung);
			printf("%10d",geraet->verbrauch);
			printf("   %5dx",geraet->hoehe);
			printf("%5dx",geraet->breite);
			printf("%5d ",geraet->tiefe);
			printf(" %7.2f\n",geraet->preis);
			i ++;
		}
	}
	if (i==0) {
		printf("Leider keine Suchtreffer...\n");
	}
	
	fclose(in);
	system("pause");
};

void sBezeichnung() {
	char suchbegriff[31];
	struct modell buffer; // lokale Variable, reserviert auch den Speicher für eine Struktur
	struct modell * geraet = &buffer;
	
	system("cls");
	
	printf("Suche Bezeichnung");
	printf("\nSuchbegriff eingeben: ");
	strcpy(suchbegriff,eingabeBezeichnung());
	printf("\nErgebnisse:\n");
	
	FILE * in;
	
	in = fopen(DATENBANK, "r");
	if (in == NULL) {
		fprintf(stderr, "Konnte die Datenbank %s nicht zum Lesen öffnen!\n", DATENBANK);
		system("pause");
		return;
	}
	
	int i=0;
	while (fread(geraet, sizeof(struct modell), 1, in) == 1) {
		if(geraet->bezeichnung[0]!='\0' ) {	
			if(vBezeichnung(suchbegriff,geraet->bezeichnung)==1) {
				if (i==0) tabellenHeader();
				printf(" %2d ",i+1);
				printf("%30s ",geraet->bezeichnung);
				printf("%10d",geraet->kleistung);
				printf("%10d",geraet->verbrauch);
				printf("   %5dx",geraet->hoehe);
				printf("%5dx",geraet->breite);
				printf("%5d ",geraet->tiefe);
				printf(" %7.2f\n",geraet->preis);
				i ++;
			}
		}
	}
	if (i==0) {
		printf("Leider keine Suchtreffer...\n");
	}
	
	fclose(in);
	system("pause");
};



int vBezeichnung(char *sBegriff,char *bezeichnung) {
	int i,j,lSBegriff,lBezeichnung,gefunden=0;
	char sTemp,bTemp;
	lSBegriff=strlen(sBegriff);
	lBezeichnung=strlen(bezeichnung);
	if(lSBegriff>lBezeichnung)return(0);
	for(i=0,j=0; i<lBezeichnung; i++,j++) 	{
		
		if(*(bezeichnung+i)>=97) bTemp=*(bezeichnung+i)-32; // zu lower case
		else bTemp=*(bezeichnung+i); // war schon lower case
		
		if(*(sBegriff+j)>=97) sTemp=*(sBegriff+j)-32; // zu lower case
		else sTemp=*(sBegriff+j); // war schon lower case
		if(bTemp==sTemp) {
			gefunden++;
		} else {
			gefunden=0;
			// Cursor des Suchbegriffs auf -1, so dass er im nächsten 
			// Schleifendurchlauf wieder bei 0 steht:
			j=-1;
		}
		// wenn alle Zeichen des Suchbegriffes gefunden worden sind:
		if(gefunden==lSBegriff) return(1);
	}
	return(0);
};

void sMenue() {
	char auswahl;
	system("cls");
	printf("Wonach soll gesucht werden?");
	printf("\n\n1.)Bezeichnung");
	printf("\n2.)K\204lteleistung");
	printf("\n3.)Stromverbrauch");
	printf("\n4.)Abmessungen");
	printf("\n5.)Preis");
	printf("\na.)abbruch");
	
	do {
		auswahl=getch();
	} while (!(auswahl>='1' && auswahl <='5') && auswahl!='a');
	
	switch(auswahl)	{
		case '1': sBezeichnung(); break;
		case '2': sKaelteleistung(); break;
		case '3': sVerbrauch();	break;
		case '4': sAbmessung();	break;
		case '5': sPreis();	break;
	}
};



