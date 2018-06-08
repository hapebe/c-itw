void speichern(struct modell * geraet) {
	FILE * out;
	
	out = fopen(DATENBANK, "a+");
	if (out == NULL) {
		fprintf(stderr, "Konnte die Datenbank %s nicht zum Schreiben öffnen!\n", DATENBANK);
		system("pause");
		return;
	}
	
	// aus dem RAM, an der Adresse von geraet beginnend, 
	// einmalig X Bytes (Größe von geraet) schreiben:
	int n = fwrite(geraet, sizeof(struct modell), 1, out);
	if (n != 1) {
		fprintf(stderr, "Konnte den Datensatz nicht speichern!\n");
		system("pause");
	}
	
	fclose(out);
}

void laden(struct modell * geraet) {
	FILE * in;
	
	system("cls");
	
	in = fopen(DATENBANK, "a+");
	if (in == NULL) {
		fprintf(stderr, "Konnte die Datenbank %s nicht zum Lesen öffnen!\n", DATENBANK);
		system("pause");
		return;
	}
	
	int i=0;
	while (fread(geraet, sizeof(struct modell), 1, in) == 1) {
		if (i==0) tabellenHeader(); // aus einAusgaben.c
		
		printf(" %2d ",i+1);
		printf("%30s ",geraet->bezeichnung);
		printf("%10d",geraet->kleistung);
		printf("%10d",geraet->verbrauch);
		printf("   %5dx",geraet->hoehe);
		printf("%5dx",geraet->breite);
		printf("%5d ",geraet->tiefe);
		printf(" %7.2f",geraet->preis);
		printf("\n");
		i++;
	}
	if (i==0) {
		fprintf(stderr, "Konnte keinen Datensatz lesen!\n");
	}
	
	system("pause");
	fclose(in);
}
