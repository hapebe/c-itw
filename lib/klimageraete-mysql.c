/**
 * kein Rückgabewert - wenn ein Fehler auftritt, wird stattdessen direkt
 * das Programm beendet.
 */
void klimageraetToDB(struct t_klimageraet *geraet) {
	char puffer[1024]; puffer[0] = '\0';
	char * p = &puffer[0];

	char numFeldPuffer[16]; numFeldPuffer[0] = '\0';
	char * p2 = &numFeldPuffer[0];

	// SQL-Statement zusammenbauen:
	strcat(p, "INSERT INTO ");
	strcat(p, DB_TABLE);
	strcat(p, " (modellBezeichnung, kaelteLeistung, stromVerbrauch, breite, hoehe, tiefe, preis)");
	strcat(p, " VALUES('");
	strcat(p, geraet->modellBezeichnung);
		strcat(p, "', ");
	sprintf(p2, "%d", geraet->kaelteLeistung);
		strcat(p, p2);
		strcat(p, ", "); // Trennzeichen
	sprintf(p2, "%d", geraet->stromVerbrauch);
		strcat(p, p2);
		strcat(p, ", "); // Trennzeichen
	sprintf(p2, "%d", geraet->breite);
		strcat(p, p2);
		strcat(p, ", "); // Trennzeichen
	sprintf(p2, "%d", geraet->hoehe);
		strcat(p, p2);
		strcat(p, ", "); // Trennzeichen
	sprintf(p2, "%d", geraet->tiefe);
		strcat(p, p2);
		strcat(p, ", "); // Trennzeichen
	sprintf(p2, "%.2f", geraet->preis);
		strcat(p, p2);
	strcat(p, ");");

#ifdef DEBUG
	printf("SQL in klimageraetToDB: %s\n", p);
#endif

	// den SQL-Befehl ausführen:
	if (mysql_query(con, p)) finishWithError(con);
}

/**
 * Liest ein komplettes Array von Klimageräten aus der Datenbank ein,
 * ersetzt dabei die bestehende "Datenbank" im RAM komplett.
 *
 * kein Rückgabewert - wenn ein Fehler auftritt, wird stattdessen direkt
 * das Programm beendet.
 */
void klimageraeteFromDB(struct t_klimageraet * ptr, int maxAnzahl) {
	int i=0;

	for (i=0; i<MAX_GERAETE; i++) {
		klimageraete[i].modellBezeichnung[0] = '\0';
		filterKlimageraete[i] = FILTER_SICHTBAR;
	}

	// 95% inspiriert von: http://zetcode.com/db/mysqlc/

	// den eigentlichen SQL-Befehl ausführen:
	char query[1024]; query[0] = '\0'; char * pQuery = &query[0];
	strcat(pQuery, "SELECT modellBezeichnung, kaelteLeistung, stromVerbrauch, breite, hoehe, tiefe, preis FROM ");
	strcat(pQuery, DB_TABLE);
	strcat(pQuery, ";");
	if (mysql_query(con, pQuery)) finishWithError(con);

	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL) finishWithError(con);

	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	i = 0;
	while ((row = mysql_fetch_row(result))) {
		// printf("Result row[%d]: ", i);
		for(int j = 0; j < num_fields; j++)	{
			// printf("%d: \"%s\"; ", j, row[j] ? row[j] : "NULL");

			switch(j) {
				case 0: strcpy(ptr->modellBezeichnung, row[j]); break;
				case 1: ptr->kaelteLeistung = atoi(row[j]); break;
				case 2: ptr->stromVerbrauch = atoi(row[j]); break;
				case 3: ptr->breite = atoi(row[j]); break;
				case 4: ptr->hoehe = atoi(row[j]); break;
				case 5: ptr->tiefe = atoi(row[j]); break;
				case 6: ptr->preis = atof(row[j]); break;
			}
		}
		// printf("\n");
		// printf("Aus der Datenbank gelesenes Gerät: \n");
		// printKlimageraetZeile(ptr);

		i ++;
		ptr ++; // nächstes Gerät...

		// wenn maximale Anzahl erreicht, abbrechen:
		if (i == maxAnzahl) break;
	}
	mysql_free_result(result);
}
