#include "./fGeheim.c"

int main(int anzahl, char *werte[])
{
	char auswahl = '\0';
	char qDateiname[65];
	char zDateiname[65];
	char kennwort[41];

	qDateiname[0] = '\0'; // also: leerer String!
	zDateiname[0] = '\0'; // also: leerer String!
	kennwort[0] = '\0'; // also: leerer String!
	
	int nGueltigeArgumente = 0;
	int i;
	// alle Argumente durchgehen:
	for (i=1; i<anzahl; i++) {
		// printf("Argument[%d]: %s\n", i, werte[i]);
		char c1 = erstesZeichenVon(werte[i]);
		// printf("Erstes Zeichen des Arguments[%d]: %c\n", i, c1);
		
		// wenn kein Argument, dann ignorieren:
		if (c1 != '/') continue;
		
		char c2 = zweitesZeichenVon(werte[i]);
		// printf("Zweites Zeichen des Arguments[%d]: %c\n", i, c2);

		// char * wertAbDem3Zeichen = werte[i]+2;
		// printf("Freitext des Arguments[%d]: %c\n", i, wertAbDem3Zeichen);
		// system("pause");
		
		switch(c2) {
			case 'q':
				nGueltigeArgumente++;
				// Quelldateiname: 
				// ALLES ab dem 3. Zeichen (egal wie lang...):
				strcpy(qDateiname, werte[i]+2);
				// nicht mehr als 64 Zeichen ab dem 3. Zeichen:
				// strncpy(qDateiname, werte[i]+2, 64);
				// printf("Quelldateiname: %s\n", qDateiname);
				break;
			case 'z':
				nGueltigeArgumente++;
				// Zieldateiname: 
				strcpy(zDateiname, werte[i]+2);
				// printf("Zieldateiname: %s\n", zDateiname);
				break;
			case 'p':
				nGueltigeArgumente++;
				// Kennwort: (Option /p... )
				strcpy(kennwort, werte[i]+2);
				// printf("Kennwort: %s\n", kennwort);
				break;
			case 'v':
				nGueltigeArgumente++;
				auswahl = 'v';
				break;
			case 'e':
				nGueltigeArgumente++;
				auswahl = 'e';
				break;
		} // case (Argument-Typ unterscheiden)
	} // for-Schleife (Argumente durchgehen)

	if (nGueltigeArgumente == 0) {
		// print usage:
		fprintf(stderr, "geheim - Textdateien ver- und entschlüsseln.\n\n");
		fprintf(stderr, "Aufruf:\n");
		fprintf(stderr, "geheim /v /q<Quelldatei> /p<Passwort> [/zZieldatei]\n");
		fprintf(stderr, "\tVerschlüsselt die Quelldatei mit dem Passwort. Wenn \n");
		fprintf(stderr, "\teine Zieldatei angegeben ist, wird in diese geschrieben, \n");
		fprintf(stderr, "\tsonst direkt in die Ausgabe.\n");
		fprintf(stderr, "geheim /e /q<Quelldatei> /p<Passwort> [/zZieldatei]\n");
		fprintf(stderr, "\tEntschlüsselt die Quelldatei mit dem Passwort. Wenn \n");
		fprintf(stderr, "\teine Zieldatei angegeben ist, wird in diese geschrieben, \n");
		fprintf(stderr, "\tsonst direkt in die Ausgabe.\n");
		fprintf(stderr, "\n");
		return 1;
	}
	
	if (auswahl == '\0') {
		printf("Fehler: Es wurde kein Modus gewählt (/v oder /e)!\n");
		return 1;
	}
	if (qDateiname[0] == '\0') {
		printf("Fehler: Es wurde keine Quelldatei angegeben (/q<Dateiname>)!\n");
		return 1;
	}
	if (kennwort[0] == '\0') {
		printf("Fehler: Es wurde kein Passwort angegeben (/p<Passwort>)!\n");
		return 1;
	}
	
	// Action!
	if (auswahl == 'v') {
		// vielleicht ist ein zDateiname gesetzt, 
		// dann sollte der verwendet werden, sonst 
		// AUF DEN BILDSCHIRM ausgeben
		// Verschlüsseln:
		verSchl(kennwort,qDateiname,zDateiname);
	} else if (auswahl == 'e') {
		// vielleicht ist ein zDateiname gesetzt, 
		// dann sollte der verwendet werden, sonst 
		// AUF DEN BILDSCHIRM ausgeben
		// Entschlüsseln:
		entSchl(kennwort,qDateiname,zDateiname);
	} else {
		// Das sollte nie passieren!!!
		printf("Weltuntergang!\n");
	}

	// system("pause");
	return 0;
}

