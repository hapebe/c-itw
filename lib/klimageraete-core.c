/**
 * Kennzeichnung "frei" oder "gültig" findet über das erste Byte in der modellBezeichnung statt: 0 bedeutet frei.
 */
struct t_klimageraet {
	char modellBezeichnung[256];
	int kaelteLeistung; // in Watt
	int stromVerbrauch; // in Watt
	int breite, hoehe, tiefe; // breite, hoehe und tiefe sollen in cm gemessen werden.
	float preis; // in Euro
};

#define FILTER_VERSTECKT 0
#define FILTER_SICHTBAR 1

#define MAX_GERAETE 100
struct t_klimageraet klimageraete[MAX_GERAETE];
int filterKlimageraete[MAX_GERAETE];

// forward declarations:
int istFreiesGeraet(struct t_klimageraet *);
int nSichtbareGeraete(void);
int einzigesSichtbaresGeraet(void);

/**
 * selbständige interaktive Prozedur: Daten eines Klimageräts neu eingeben
 */
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

/**
 * selbständige interaktive Prozedur: Daten eines Klimageräts pro Eigenschaft
 * ausgeben und dann entweder übernehmen oder neu eingeben
 */
void aendereKlimageraet(struct t_klimageraet * geraet) {
	char * ptrPuffer;
	int temp;

	printf("Bitte geben sie die neuen Daten ein! Wenn Sie eine leere Eingabe machen, wird der bestehende Wert übernommen.\n\n");
	textEingabeAcceptEmpty = -1;

	printf("Modellbezeichnung (ist: %s):\n", geraet->modellBezeichnung);
	ptrPuffer = texteingabeLength(255);
	if (strlen(ptrPuffer) > 0) strcpy(geraet->modellBezeichnung, ptrPuffer);

	printf("Kälteleistung (Watt) (ist: %d):\n", geraet->kaelteLeistung);
	temp = eingabeIntGr0OderLeer("Die Kälteleistung muss größer als 0 sein, bitte wiederholen:");
	if (temp > 0) geraet->kaelteLeistung = temp;

	printf("Stromverbrauch (Watt) (ist: %d):\n", geraet->stromVerbrauch);
	temp = eingabeIntGr0OderLeer("Der Stromverbrauch muss größer als 0 sein, bitte wiederholen:");
	if (temp > 0) geraet->stromVerbrauch = temp;

	printf("Abmessungen - Breite (cm) (ist: %d):\n", geraet->breite);
	temp = eingabeIntGr0OderLeer("Die Breite muss größer als 0 sein, bitte wiederholen:");
	if (temp > 0) geraet->breite = temp;
	printf("Abmessungen - Höhe (cm) (ist: %d):\n", geraet->hoehe);
	temp = eingabeIntGr0OderLeer("Die Höhe muss größer als 0 sein, bitte wiederholen:");
	if (temp > 0) geraet->hoehe = temp;
	printf("Abmessungen - Tiefe (cm) (ist: %d):\n", geraet->tiefe);
	temp = eingabeIntGr0OderLeer("Die Tiefe muss größer als 0 sein, bitte wiederholen:");
	if (temp > 0) geraet->tiefe = temp;

	printf("Preis (EUR) (ist: %5.2f):\n", geraet->preis);
	float tempF = eingabePreisOderLeer();
	if (!flagLeereEingabe) geraet->preis = tempF;
}

/**
 * schreibt einen "BxHxT"-String für die Daten eines Klimageräts
 */
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

/**
 * Gibt eine formatierte Einzelansicht eines Klimageräts aus.
 */
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

/**
 * gibt eine auf die Tabellen-Ansicht formatierte Zeile für ein Klimagerät aus
 */
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

/**
 * @return -1 wenn dieses Gerät als frei markiert ist; 0, wenn es "belegt" (gültig) ist
 */
int istFreiesGeraet(struct t_klimageraet * p) {
	// printf("Modellbezeichnung: %s\n", p->modellBezeichnung);

	if (p->modellBezeichnung[0] == '\0') return -1;
	return 0;
}

/**
 * ermöglicht die Auswahl einer gültigen Datensatznummer, oder Abbruch bei leerer Eingabe:
 * @return gültiger Index von klimageraete[] oder -1 für Abbruch
 */
int datensatzWaehlenOderAbbruch(char * prompt) {
	// Sonderfall behandeln: Wenn es nur genau ein Gerät gibt, gilt
	// dieses automatisch als ausgewählt, ABER: Abbruch muss möglich sein -
	// also eine Art Bestätigungsabfrage...
	if (nSichtbareGeraete() == 1) {
		int index = einzigesSichtbaresGeraet();

		if (confirm("\nMeinen Sie dieses Gerät (j/n)? ") == 0) return -1; // Abbruch

		return index;
	}


	static char buffer[32];
	char * ptrBuffer = &buffer[0];

	printf("%s", prompt);
	do {
		fgets(ptrBuffer, 31, stdin);
		// dump(trim(ptrBuffer)); warteAufTaste(); // DEBUG

		if (strlen(trim(ptrBuffer)) == 0) return -1; // Schleife und Funktion verlassen

		int index = atoi(trim(ptrBuffer));
		if (index < 0 || index >= MAX_GERAETE) {
			printf("%d ist keine gültige Geräte-Nummer.\n", index);
		} else if (istFreiesGeraet(&klimageraete[index])) {
			printf("Nummer %d enthält keinen Datensatz.\n", index);
		} else {
			return index;
		}
	} while(-1); // wird per return verlassen
}

/**
 * gibt die Anzahl vorhandener Klimageräte zurück
 */
int nGeraete(void) {
	int n = 0;

	int i;
	for (i=0; i<MAX_GERAETE; i++) {
		if (!istFreiesGeraet(&klimageraete[i])) n++;
	}
	return n;
}

/**
 * gibt die Anzahl sichtbarer Klimageräte zurück
 */
int nSichtbareGeraete(void) {
	int n = 0;

	int i;
	for (i=0; i<MAX_GERAETE; i++) {
		if (!istFreiesGeraet(&klimageraete[i]) && filterKlimageraete[i] == FILTER_SICHTBAR) n++;
	}
	return n;
}

/**
 * @return index des einzigen sichtbaren Gerätes, wenn es denn tatsächlich nur eines gibt - sonst DIE!
 */
int einzigesSichtbaresGeraet(void) {
	int n = 0;
	int retval = -1;

	int i;
	for (i=0; i<MAX_GERAETE; i++) {
		if (!istFreiesGeraet(&klimageraete[i]) && filterKlimageraete[i] == FILTER_SICHTBAR) {
			retval = i;
			n++;
		}
	}

	if (n != 1) die("einzigesSichtbaresGeraet(): Fehler - es gibt nicht genau ein sichtbares Gerät!");
	return retval;
}

/**
 * @return index eines freien Datensatzes in klimageraete[] oder -1, wenn es keine freien Plätze gibt.
 */
int getFreiesGeraet(void) {
	int i;
	for (i=0; i<MAX_GERAETE; i++) {
		if (istFreiesGeraet(&klimageraete[i])) return i;
	}
	return -1;
}

