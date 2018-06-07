/**
 * Enthält Vorbereitungen von Test-Daten und Code zu
 * automatisierten Tests des Programms klimageraete.c .
 *
 * Sollte im fertigen Programm im Lieferzustand nicht mehr referenziert
 * werden!
 */

void initTest() {
#ifndef DEBUG
	die("initTest() wurde aufgerufen, obwohl der Debug-Modus nicht aktiv ist.");
#endif

	// benutzt globale Variablen:
	// struct t_klimageraete klimageraete[MAX_GERAETE];

	// wenn an dieser Stelle schon Geräte vorhanden sind, dann NICHT
	// die Testdaten anlegen:
	if (nGeraete() > 0) return;

	int i;
	struct t_klimageraet * ptr;


	// Erstes:
	i = 0;
	ptr = &klimageraete[i];
	strcpy(ptr->modellBezeichnung, "Arctica Deluxe 7000 XPE");
	ptr->kaelteLeistung = 7000;
	ptr->stromVerbrauch = 3600;
	ptr->breite = 80;
	ptr->hoehe = 120;
	ptr->tiefe = 45;
	ptr->preis = 1259.50;

	// Zweites:
	i++;
	ptr = &klimageraete[i];
	strcpy(ptr->modellBezeichnung, "DeLonghi Summer-Master Superforte - dies ist ein sehr, sehr langer Text für die Modellbezeichnung, mit dem ich die Auswirkungen eben solcher im Programm testen möchte");
	ptr->kaelteLeistung = 4000;
	ptr->stromVerbrauch = 2200;
	ptr->breite = 70;
	ptr->hoehe = 90;
	ptr->tiefe = 40;
	ptr->preis = 830.00;

	// Drittes:
	i++;
	ptr = &klimageraete[i];
	strcpy(ptr->modellBezeichnung, "itw Special Edition 2018");
	ptr->kaelteLeistung = -200;
	ptr->stromVerbrauch = 150;
	ptr->breite = 50;
	ptr->hoehe = 50;
	ptr->tiefe = 50;
	ptr->preis = 12.34;

	// explizit adressiertes:
	i=20;
	ptr = &klimageraete[i];
	strcpy(ptr->modellBezeichnung, "obi-NoName #1");
	ptr->kaelteLeistung = 2200;
	ptr->stromVerbrauch = 2100;
	ptr->breite = 60;
	ptr->hoehe = 40;
	ptr->tiefe = 35;
	ptr->preis = 399.90;

}

/**
 * schreibt den Belegungs-Status und die Sichtbarkeit aller
 * Speicherplätze für Klimageräte auf den Bildschirm.
 */
void debugPrintStatus() {
	int i;
	printf("status:\n");
	for (i=0; i<MAX_GERAETE; i++) {
		printf("%d ", istFreiesGeraet(&klimageraete[i])?0:1 );
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


void testEingabeLeererInt() {
	printf("Leere int-Eingabe erkennen:\n");
	textEingabeAcceptEmpty = -1;
	char * p = texteingabeLengthSet(9,DEZIMAL_ZIFFERN);
	if (strlen(p) == 0) printf("Leere Eingabe!"); else printf("Keine leere Eingabe: %d", atoi(p));
	printf("\n");

}

void testEingabeLeererPreis() {
	printf("Leere float-Eingabe (Preis) erkennen:\n");
	textEingabeAcceptEmpty = -1;
	float tempF = eingabePreisOderLeer();

	if (flagLeereEingabe) printf("Leere Eingabe!"); else printf("Keine leere Eingabe: %f", tempF);
	printf("\n");
}
