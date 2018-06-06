#include <stdio.h>
#include <conio.h>
#include <windows.h>

/**
 * gibt das erste Zeichen einer Zeichenkette zur¸ck
 */
char erstesZeichenVon(char* string) {
	return *string; // d.h. den Wert an der Speicherstelle, auf die *string zeigt
}

/**
 * gibt das zweite Zeichen einer Zeichenkette zur¸ck
 */
char zweitesZeichenVon(char* string) {
	return *(string+1); // d.h. den Wert 1 char nach der Speicherstelle, auf die *string zeigt
}




void entSchl(char *kennwort, char *qDateiname, char *zDateiname) {
	char temp;
	int lKennwort=strlen(kennwort);
	FILE *out,*in;
	
	if(NULL==(in=fopen(qDateiname,"r"))) {
		printf("Datei %s nicht vorhanden!\n", qDateiname);
		return;
	}

	if (zDateiname[0] == '\0') {
		// es wurde kein Dateiname angegeben - es 
		// soll auf den Bildschirm geschrieben werden!
		out = stdout;
		printf("Der Text entschl\201sselt\n\n");
	} else {
		if(NULL==(out=fopen(zDateiname,"w"))) {
			printf("Datei %s konnte nicht erstellt werden!\n", zDateiname);
			fclose(in); // an dieser Stelle war die Quell-Datei schon geˆffnet...
			return;
		}
	}


	// hier ist jetzt sicher, dass sowohl in als 
	// auch out erfolgreich geˆffnet worden sind!

	int i=0;
	while( (temp=fgetc(in)) != EOF) {
		if(i>=lKennwort)i=0;
		putch(temp-*(kennwort+i));
		i++;
	}
	
	// falls wir stdout benutzt haben: nicht schlieﬂen!
	if (out != stdout) fclose(out);
	// die Quelldatei aber immer:
	fclose(in);

	// nur, wenn wir einen Zieldateinamen hatten:
	if (zDateiname[0] != '\0') {
		printf("Die Datei %s wurde entschl\201sselt\n und als Datei %s gespeichert.\n\n",
				qDateiname,zDateiname);
	}
				
	return; // br‰uchten wir nicht, aber zur Illustration...
};


void verSchl(char *kennwort, char *qDateiname, char* zDateiname) {
	char temp;
	int lKennwort=strlen(kennwort);
	FILE *out,*in;
	
	if(NULL==(in=fopen(qDateiname,"r"))) {
		printf("Datei %s nicht vorhanden!\n", qDateiname);
		return;
	}

	if (zDateiname[0] == '\0') {
		// es wurde kein Dateiname angegeben - es 
		// soll auf den Bildschirm geschrieben werden!
		out = stdout;
	} else {
		if(NULL==(out=fopen(zDateiname,"w"))) {
			printf("Datei %s konnte nicht erstellt werden!\n", zDateiname);
			fclose(in); // an dieser Stelle war die Quell-Datei schon geˆffnet...
			return;
		}
	}


	// hier ist jetzt sicher, dass sowohl in als 
	// auch out erfolgreich geˆffnet worden sind!

	int i=0;
	while( (temp=fgetc(in)) != EOF) {
		if(i>=lKennwort)i=0;
		fputc(temp+*(kennwort+i),out);
		i++;
	}
	
	// falls wir stdout benutzt haben: nicht schlieﬂen!
	if (out != stdout) fclose(out);
	// die Quelldatei aber immer:
	fclose(in);

	// nur, wenn wir einen Zieldateinamen hatten:
	if (zDateiname[0] != '\0') {
		printf("Die Datei %s wurde veschl\201sselt\n und als Datei %s gespeichert\n\n",
				qDateiname,zDateiname);
	}
				
	return; // br‰uchten wir nicht, aber zur Illustration...
};

