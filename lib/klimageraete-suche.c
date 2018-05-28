void filterAlleVersteckt() {
	int i;
	// alle Datensätze herausfiltern (VERSTECKT)
	for (i=0; i<MAX_GERAETE; i++) filterKlimageraete[i] = FILTER_VERSTECKT;
}

void filterAlleSichtbar() {
	int i;
	// alle Datensätze durchlassen (SICHTBAR)
	for (i=0; i<MAX_GERAETE; i++) filterKlimageraete[i] = FILTER_SICHTBAR;
}


int sucheModellBezeichnung() {
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

	if (strlen(ptrA) == 0) {
		printf("Sie haben keinen Suchausdruck eingegeben - die Suche wird abgebrochen.\n\n");
		warteAufTaste();
		return -1;
	}

	// in Kleinbuchstaben umwandeln
	toLowerCase(ptrB, ptrA);
	// printf("Suchbegriff: %s\n", ptrB); warteAufTaste(); // DEBUG

	filterAlleVersteckt();

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
	return 1;
}

void sucheKaelteLeistung() {
	int i;

	cls();
	printf("Suchen (Schritt 2)\n");
	printf("\n");
	printf("Bitte geben Sie die gewünschte Mindest-Kälteleistung ein: \n");

	int q = eingabeIntGr0("Bei 0 müssen Sie gar nicht erst suchen - bitte etwas mehr eingeben.");
	// printf("q=%d\n", q); warteAufTaste(); // DEBUG

	filterAlleVersteckt();

	// alle belegten Datensätze nach Matches durchsuchen
	for (i=0; i<MAX_GERAETE; i++) {
		if (statusKlimageraete[i] == FREI) continue;

		if (klimageraete[i].kaelteLeistung >= q) {
			// printf("%d: %d <> %d : %d\n", i, klimageraete[i].kaelteLeistung, q, (klimageraete[i].kaelteLeistung >= q));
			filterKlimageraete[i] = FILTER_SICHTBAR;
		}
	}
	// debugPrintStatus(); warteAufTaste();

	// fertig - die Anzeige erfolgt in der aufrufenden Funktion
}

void sucheElektLeistung() {
	int i;

	cls();
	printf("Suchen (Schritt 2)\n");
	printf("\n");
	printf("Bitte geben Sie den gewünschten maximalen Stromverbrauch ein:  ");

	int q = eingabeIntGr0("Bei 0 müssen Sie gar nicht erst suchen - bitte etwas mehr eingeben: ");
	// printf("q=%d\n", q); warteAufTaste(); // DEBUG

	filterAlleVersteckt();

	// alle belegten Datensätze nach Matches durchsuchen
	for (i=0; i<MAX_GERAETE; i++) {
		if (statusKlimageraete[i] == FREI) continue;

		if (klimageraete[i].stromVerbrauch <= q) {
			// printf("%d: %d <> %d : %d\n", i, klimageraete[i].kaelteLeistung, q, (klimageraete[i].kaelteLeistung >= q));
			filterKlimageraete[i] = FILTER_SICHTBAR;
		}
	}
	// debugPrintStatus(); warteAufTaste();

	// fertig - die Anzeige erfolgt in der aufrufenden Funktion
}

int sucheAbmessungen() {
	int i;
	static char buffer[32];
	char * ptrBuffer = &buffer[0];

	cls();
	printf("Suchen (Schritt 2)\n");
	printf("\n");
	printf("Bitte geben Sie jeweils das maximale Maß ein, oder gar nichts für \"egal\": \n");

	int qBreite = -1;
	printf("Breite (cm): ");
	do {
		fgets(ptrBuffer, 31, stdin);
		// dump(trim(ptrBuffer)); warteAufTaste(); // DEBUG

		if (strlen(trim(ptrBuffer)) == 0) break;

		int i = atoi(trim(ptrBuffer));
		if (i <= 0) {
			printf("Bitte einen Wert größer als 0 eingeben: ");
		} else {
			qBreite = i;
			break;
		}
	} while(-1); // wird per break verlassen

	int qHoehe = -1;
	printf("Höhe (cm): ");
	do {
		fgets(ptrBuffer, 31, stdin);
		// dump(trim(ptrBuffer)); warteAufTaste(); // DEBUG

		if (strlen(trim(ptrBuffer)) == 0) break;

		int i = atoi(trim(ptrBuffer));
		if (i <= 0) {
			printf("Bitte einen Wert größer als 0 eingeben: ");
		} else {
			qHoehe = i;
			break;
		}
	} while(-1); // wird per break verlassen

	int qTiefe = -1;
	printf("Tiefe (cm): ");
	do {
		fgets(ptrBuffer, 31, stdin);
		// dump(trim(ptrBuffer)); warteAufTaste(); // DEBUG

		if (strlen(trim(ptrBuffer)) == 0) break;

		int i = atoi(trim(ptrBuffer));
		if (i <= 0) {
			printf("Bitte einen Wert größer als 0 eingeben: ");
		} else {
			qTiefe = i;
			break;
		}
	} while(-1); // wird per break verlassen

	// haben wir mindestens ein sinnvolles Kriterium?
	if (qBreite == -1 && qHoehe == -1 && qTiefe && -1) {
		printf("Sie haben kein Suchkriterium eingegeben - die Suche wird abgebrochen...\n\n");
		warteAufTaste();
		return -1;
	}


	// Suche durchführen:
	filterAlleVersteckt();

	// alle belegten Datensätze nach Matches durchsuchen
	for (i=0; i<MAX_GERAETE; i++) {
		if (statusKlimageraete[i] == FREI) continue;

		int match = -1;
		if (qBreite >= 0 && klimageraete[i].breite > qBreite) match = 0;
		if (qHoehe >= 0 && klimageraete[i].hoehe > qHoehe) match = 0;
		if (qTiefe >= 0 && klimageraete[i].tiefe > qTiefe) match = 0;
		if (match) {
			filterKlimageraete[i] = FILTER_SICHTBAR;
		}
	}
	// debugPrintStatus(); warteAufTaste();

	// fertig - die Anzeige erfolgt in der aufrufenden Funktion
	return 1;
}

void suchePreis() {
	int i;

	cls();
	printf("Suchen (Schritt 2)\n");
	printf("\n");
	printf("Bitte geben Sie die gewünschte Preisspanne ein:\n");

	float qMin = 0, qMax = 0;
	do {
		printf("Mindestpreis: \n");
		qMin = eingabePreis();

		printf("Höchstpreis: \n");
		qMax = eingabePreis();

		// printf("q=%d\n", q); warteAufTaste(); // DEBUG

		if (qMax < qMin) {
			printf("Sie haben einen Höchstpreis angegeben, der niedriger ist als der Mindestpreis - bitte wiederholen!\n");
		} else {
			break;
		}
	} while (-1);

	filterAlleVersteckt();

	// alle belegten Datensätze nach Matches durchsuchen
	for (i=0; i<MAX_GERAETE; i++) {
		if (statusKlimageraete[i] == FREI) continue;

		if (klimageraete[i].preis >= qMin && klimageraete[i].preis <= qMax) {
			// printf("%d: %d <> %d : %d\n", i, klimageraete[i].kaelteLeistung, q, (klimageraete[i].kaelteLeistung >= q));
			filterKlimageraete[i] = FILTER_SICHTBAR;
		}
	}
	// debugPrintStatus(); warteAufTaste();

	// fertig - die Anzeige erfolgt in der aufrufenden Funktion
}


