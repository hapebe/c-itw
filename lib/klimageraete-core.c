struct t_klimageraet {
	char modellBezeichnung[256];
	int kaelteLeistung; // in Watt
	int stromVerbrauch; // in Watt
	int breite, hoehe, tiefe; // breite, hoehe und tiefe sollen in cm gemessen werden.
	float preis; // in Euro
};

// soll kennzeichnen, ob ein Eintrag in klimageraete vorhanden ist oder nicht:
#define FREI 0
#define BELEGT 1

#define FILTER_VERSTECKT 0
#define FILTER_SICHTBAR 1

#define MAX_GERAETE 100
struct t_klimageraet klimageraete[MAX_GERAETE];
int statusKlimageraete[MAX_GERAETE];
int filterKlimageraete[MAX_GERAETE];

void debugPrintStatus() {
	int i;
	printf("status:\n");
	for (i=0; i<MAX_GERAETE; i++) {
		printf("%d ", statusKlimageraete[i]);
		if ((i+1) % 10 == 0) printf("\n");
	}
	printf("\n");
	printf("filter:\n");
	for (i=0; i<MAX_GERAETE; i++) {
		printf("%d ", filterKlimageraete[i]);
		if ((i+1) % 10 == 0) printf("\n");
	}
	printf("\n");
}

void eingabeKlimageraet(struct t_klimageraet * geraet) {
	do {
		printf("Modellbezeichnung:\n");
		strcpy(geraet->modellBezeichnung, texteingabeLength(255));
		if (strlen(geraet->modellBezeichnung) == 0) {
			printf("Die Bezeichnung darf nicht leer sein!\n");
		} else {
			break;
		}
	} while (-1);
	printf("Kälteleistung (Watt):\n");
	geraet->kaelteLeistung = eingabeIntGr0("Die Kälteleistung muss größer als 0 sein, bitte wiederholen:");
	printf("Stromverbrauch (Watt):\n");
	geraet->stromVerbrauch = eingabeIntGr0("Der Stromverbrauch muss größer als 0 sein, bitte wiederholen:");
	printf("Abmessungen - Breite (cm):\n");
	geraet->breite = eingabeIntGr0("Die Breite muss größer als 0 sein, bitte wiederholen:");
	printf("Abmessungen - Höhe (cm):\n");
	geraet->hoehe = eingabeIntGr0("Die Höhe muss größer als 0 sein, bitte wiederholen:");
	printf("Abmessungen - Tiefe (cm):\n");
	geraet->tiefe = eingabeIntGr0("Die Tiefe muss größer als 0 sein, bitte wiederholen:");
	printf("Preis (EUR):\n");
	geraet->preis = eingabePreis();
}

void writeKlimageraetBHT(char* dest, struct t_klimageraet * geraet) {
	static char buffer[32];
	char * ptrBuffer = &buffer[0];

	dest[0] = '\0';
	sprintf(ptrBuffer, "%d", geraet->breite);
	strcat(dest, ptrBuffer);
	strcat(dest, "x");
	sprintf(ptrBuffer, "%d", geraet->hoehe);
	strcat(dest, ptrBuffer);
	strcat(dest, "x");
	sprintf(ptrBuffer, "%d", geraet->tiefe);
	strcat(dest, ptrBuffer);
}

void ausgabeKlimageraet(struct t_klimageraet * geraet) {
	static char buffer[32];
	char * ptrBuffer = &buffer[0];
	static char b2[32];
	char * ptrB2 = &b2[0];


	printf("Modellbezeichnung:      %s\n", geraet->modellBezeichnung);
	printf("Kälteleistung (Watt):   %18d\n", geraet->kaelteLeistung);
	printf("Stromverbrauch (Watt):  %18d\n", geraet->stromVerbrauch);

	writeKlimageraetBHT(ptrBuffer, geraet);
	linksAuffuellen(ptrB2, ptrBuffer, 18);
	printf("Abmessungen (BxHxT cm): %s\n", ptrB2);

	printf("Preis (EUR):            %18.2f\n", geraet->preis);
}


void printKlimageraetZeilenUeberschrift() {
	printf("Bezeichnung         "); // 20Z
	printf(" ");
	printf("K.-lstg.  "); // @21 10Z
	printf(" ");
	printf("El. Lstg. "); // @32 10Z
	printf(" ");
	printf("Abmessungen       "); // @43 18Z
	printf(" ");
	printf("Preis      "); // @62 11Z

	printf("\n");
}

void printKlimageraetZeilenUntertitel() {
	printf("                    "); // 20Z
	printf(" ");
	printf("(Watt)    "); // @21 10Z
	printf(" ");
	printf("(Watt)    "); // @32 10Z
	printf(" ");
	printf("(BxHxT cm)        "); // @43 18Z
	printf(" ");
	printf("(EUR)      "); // @62 11Z

	printf("\n");
}

void printKlimageraetZeilenSeparator() {
	printf("===================="); // 20Z
	printf("|");
	printf("=========="); // @21 10Z
	printf("|");
	printf("=========="); // @32 10Z
	printf("|");
	printf("=================="); // @43 18Z
	printf("|");
	printf("==========="); // @62 11Z

	printf("\n");
}

void printKlimageraetZeile(struct t_klimageraet * geraet) {
	static char bufferA[256];
	char * ptrBufferA = &bufferA[0];

	static char bufferB[256];
	char * ptrBufferB = &bufferB[0];

	// Bezeichnung, ggf. auf 20 Zeichen gekürzt, ggf. auf 20 Zeichen aufgefüllt:
	kuerzen(ptrBufferA, geraet->modellBezeichnung, 20);
	rechtsAuffuellen(ptrBufferB, ptrBufferA, 20);
	printf("%s", ptrBufferB);

	// Separator:
	printf(" ");

	printf("%10d", geraet->kaelteLeistung);
	printf(" ");
	printf("%10d", geraet->stromVerbrauch);
	printf(" ");

	// BxHxT
	writeKlimageraetBHT(ptrBufferA, geraet);
	kuerzen(ptrBufferB, ptrBufferA, 18);
	linksAuffuellen(ptrBufferA, ptrBufferB, 18);
	printf("%s", ptrBufferA);

	printf(" ");
	printf("  %9.2f", geraet->preis);
	printf("\n");
}

