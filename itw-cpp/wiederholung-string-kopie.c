#include <stdio.h>
#include <string.h>

int main(void) {
	char original[] = "Es ist heiss heute.";
	char kopie[20];
	int l, i;
	
	i = 0;
	while (i < strlen(original)) {
		kopie[i] = original[i];
		i++;
	}
	kopie[i] = '\0';
	printf("Kopierte Zeichenkette: %s", kopie);
	
	return 0;
}
