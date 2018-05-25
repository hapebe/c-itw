void sucheModellBezeichnung() {
	int i;

	static char pufferA[256];
	char * ptrA = &pufferA[0];
	static char pufferB[256];
	char * ptrB = &pufferB[0];

	cls();

	printf("Suchen (Schritt 2)\n");
	printf("\n");
	printf("Bitte geben Sie einen Text ein, der in der Modellbezeichnung vorkommen muss: \n");

	// Suchbegriff eingeben
	ptrA = trim(texteingabeLength(255));
	// in Kleinbuchstaben umwandeln
	toLowerCase(ptrB, ptrA);
	// printf("Suchbegriff: %s\n", ptrB); warteAufTaste(); // DEBUG

	// alle Datensätze herausfiltern (VERSTECKT)
	for (i=0; i<MAX_GERAETE; i++) filterKlimageraete[i] = FILTER_VERSTECKT;

	// alle belegten Datensätze (in Kleinbuchstaben umwandeln!) nach Matches durchsuchen
	for (i=0; i<MAX_GERAETE; i++) {
		if (statusKlimageraete[i] == FREI) continue;

		// prtB enthält den Suchbegriff...

		toLowerCase(ptrA, &(klimageraete[i].modellBezeichnung[0]));
		// printf("Vergleichs-String: %s\n", ptrA); warteAufTaste(); // DEBUG

		char * match = strstr(ptrA, ptrB);
		// ggf. Filter SICHTBAR setzen
		if ((long int)match != 0) {
			filterKlimageraete[i] = FILTER_SICHTBAR;
		}
	}

	// fertig - die Anzeige erfolgt in der aufrufenden Funktion
}

void sucheKaelteLeistung() {
	int i;

	cls();

	printf("Suchen (Schritt 2)\n");
	printf("\n");
	printf("Bitte geben Sie die gewünschte Mindest-Kälteleistung ein: \n");

	int q = eingabeIntGr0("Bei 0 müssen Sie gar nicht erst suchen - bitte etwas mehr eingeben.");
	// printf("q=%d\n", q); warteAufTaste(); // DEBUG

	// alle Datensätze herausfiltern (VERSTECKT)
	for (i=0; i<MAX_GERAETE; i++) filterKlimageraete[i] = FILTER_VERSTECKT;

	// alle belegten Datensätze nach Matches durchsuchen
	for (i=0; i<MAX_GERAETE; i++) {
		if (statusKlimageraete[i] == FREI) continue;

		if (klimageraete[i].kaelteLeistung >= q) {
			// printf("%d: %d <> %d : %d\n", i, klimageraete[i].kaelteLeistung, q, (klimageraete[i].kaelteLeistung >= q));
			filterKlimageraete[i] = FILTER_SICHTBAR;
		}
	}
	debugPrintStatus();
	warteAufTaste();

	// fertig - die Anzeige erfolgt in der aufrufenden Funktion
}
