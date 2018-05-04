#include <stdio.h>
#define GUTEN_MORGEN "Guten Morgen!"

int main(void) 
{
	int i=0;
	for (i=0; i<10; i++)
	{
		printf(GUTEN_MORGEN);
		printf("\n");
	}
	
	printf("Jetzt kann der Tag beginnen.\n");
	return 0;
}
