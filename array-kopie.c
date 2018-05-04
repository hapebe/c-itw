#include <stdio.h>
#include "lib/dump.c"

int main(void) 
{
	char ende[] = "Fast geschafft, aber noch nicht ganz. ‹blicherweise keine Umlautﬂ*";
	
	
	char kopie[sizeof(ende)];
	// printf("%d - %d", sizeof(ende), sizeof(kopie));
	
	int i=0;
	for (i=0; i<sizeof(ende); i++) {
		kopie[i] = ende[i];
	}
	
	printf ("%s\n", kopie);
	
	printf("\nDump vom kopie:\n");
	dump(kopie);	
	
	return 0;
}
