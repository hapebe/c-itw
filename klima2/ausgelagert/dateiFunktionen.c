void speichern(struct modell * geraet) {
	FILE * out;
	
	out = fopen(DATENBANK, "a+b");
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

/**
 * ggf. muss NACH dem Aufruf system("pause") benutzt werden - ist hier nicht inklusive.
 */
void alleAusgeben() {
	FILE * in;

	struct modell buffer; // lokale Variable, reserviert auch den Speicher für eine Struktur
	struct modell * geraet = &buffer;

	system("cls");
	
	in = fopen(DATENBANK, "a+b");
	if (in == NULL) {
		fprintf(stderr, "Konnte die Datenbank %s nicht zum Lesen öffnen!\n", DATENBANK);
		return;
	}
	
	int i=0, vorhanden=0;
	while (fread(geraet, sizeof(struct modell), 1, in) == 1) {
		i++;

		// ist das Gerät gar nicht gültig / ist der Datensatz leer?
		if (geraet->bezeichnung[0] == '\0') continue;
		
		if (vorhanden==0) tabellenHeader(); // aus einAusgaben.c
		
		ausgabeZeile(i, geraet); // aus einAusgaben.c
		
		vorhanden ++;
	}
	if (vorhanden==0) {
		fprintf(stderr, "Keine Datensätze vorhanden!\n");
	}
	
	fclose(in);
}

void loeschen() {
	struct modell buffer; // lokale Variable, reserviert auch den Speicher für eine Struktur
	struct modell * geraet = &buffer;
	
	system("cls");
	
	// Tabelle der Geräte anzeigen:
	alleAusgeben();
	printf("\n");
	
	printf("Geben Sie die Nummer des zu l\224schenden Produkts ein: ");
	int temp=-1;
	while (temp>=MAX || temp<0) {
		temp = eDouble(2,0)-1;
	}
	printf("\n");

	// Datei öffnen (vorher wurde sie noch im Lese-Zugriff benutzt!)
	FILE * f = fopen(DATENBANK, "r+b");
	if (f == NULL) {
		fprintf(stderr, "Konnte die Datenbank %s nicht zum Lesen+Schreiben öffnen!\n", DATENBANK);
		system("pause");
		return;
	}
	
	// springe zur Position des zu löschenden Geräts:
	int seekResult = fseek(f, temp*(sizeof(struct modell)), SEEK_SET);
	if (seekResult != 0) {
		fclose(f);
		printf("Dieses Produkt wurde in der Datenbank nicht gefunden.\n");
		system("pause");
		return;
	}

	// ist da überhaupt was?
	if (fread(geraet, sizeof(struct modell), 1, f) != 1) {
		fclose(f);
		printf("Lesefehler!\n");
		system("pause");
		return;
	}
	if (geraet->bezeichnung[0] == '\0') {
		fclose(f);
		printf("Dieses Gerät existiert gar nicht.\n");
		system("pause");
		return;
	}
	
	system("cls");
	
	// als leer / ungültig markieren:
	geraet->bezeichnung[0] = '\0';
	
	// springe erneut zur Position des zu löschenden Geräts:
	seekResult = fseek(f, temp*(sizeof(struct modell)), SEEK_SET);
	if (seekResult != 0) {
		fclose(f);
		printf("Problem mit dem Schreiben in die Datenbank.\n");
		system("pause");
		return;
	}

	// wieder speichern:
	if (fwrite(geraet, sizeof(struct modell), 1, f) != 1) {
		fclose(f);
		printf("Schreibfehler!\n");
		system("pause");
		return;
	}

	fclose(f);
	printf("Gerät Nr. %d gelöscht!\n", temp+1);
	system("pause");
}


void ersetzen()
{
	struct modell buffer; // lokale Variable, reserviert auch den Speicher für eine Struktur
	struct modell * geraet = &buffer;

	system("cls");
	
	// die Tabelle der aktuellen Geräte anzeigen:
	alleAusgeben();
	printf("\n");
	printf("Geben Sie die Nummer des zu ersetzenden Produkts ein:");
	
	int temp=-1;
	while (temp>=MAX || temp<0) {
		temp = eDouble(2,0)-1;
	}
	
	// Datei öffnen (vorher wurde sie noch im Lese-Zugriff benutzt!)
	FILE * f = fopen(DATENBANK, "r+b");
	if (f == NULL) {
		fprintf(stderr, "Konnte die Datenbank %s nicht zum Lesen+Schreiben öffnen!\n", DATENBANK);
		system("pause");
		return;
	}

	// springe zur Position des zu ersetzenden Geräts:
	int seekResult = fseek(f, temp*(sizeof(struct modell)), SEEK_SET);
	if (seekResult != 0) {
		fclose(f);
		printf("Dieses Produkt wurde in der Datenbank nicht gefunden.\n");
		system("pause");
		return;
	}
	
	// ist da überhaupt was?
	if (fread(geraet, sizeof(struct modell), 1, f) != 1) {
		fclose(f);
		printf("Lesefehler!\n");
		system("pause");
		return;
	}

	if (geraet->bezeichnung[0] == '\0') {
		printf("\n\nNeues Produkt anlegen(J/N)");
	} else {
		system("cls");
		
		// bestehendes Geräte ausgeben:
		tabellenHeader();
		ausgabeZeile(temp+1, geraet);
		printf("\n\nProdukt \201berschreiben(J/N):");
	}
		
	if(antwort()=='J')
	{
		system("cls");
		gotoxy(20,0);
		printf("Neues Produkt %d eingeben",temp+1);
		eingabe(geraet);
		printf("\n");
		
		// springe zur Position des zu ersetzenden Geräts:
		int seekResult = fseek(f, temp*(sizeof(struct modell)), SEEK_SET);
		if (seekResult != 0) {
			fclose(f);
			printf("Fehler beim Speichern (seek).\n");
			system("pause");
			return;
		}
		
		int writeResult = fwrite(geraet, sizeof(struct modell), 1, f);
		if (writeResult != 1) {
			fclose(f);
			printf("Fehler beim Speichern (write).\n");
			system("pause");
			return;
		}
		
		fclose(f);
		printf("Das Gerät wurde ersetzt.\n");
		system("pause");
		return;
	}
	
};

