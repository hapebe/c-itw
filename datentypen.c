#include <stdio.h>
#include <float.h>
void checkFloat(float f);

int main(void) 
{
	unsigned int ganzzahl = 0xffffffff; // = 11;
	// ganzzahl -= 8;
	printf("Inhalt von ganzzahl: %u.\n", ganzzahl);
	printf("Inhalt von ganzzahl (signed): %d.\n", ganzzahl);
	printf("und die Anzahl der Bytes: %d.\n", sizeof(ganzzahl));

	printf("\n");
	short kurz = 0x7fff;
	printf("Inhalt von kurz: 0x%x.\n");
	printf("und die Anzahl der Bytes: %d.\n", sizeof(kurz));
	
	printf("\n");
	float fliess = 0.5;
	printf("Inhalt von fliess: %E ; Anzahl der Bytes: %d.\n", fliess, sizeof(fliess));
	printf("\n");
	printf("float - Extremwerte und deren Bitmuster:\n");
	printf("(die verwendeten Konstanten werden in <float.h> definiert)");
	// see: http://en.cppreference.com/w/c/types/limits
	printf("0.0: "); checkFloat(0.0);
	printf("FLT_MIN: "); checkFloat(FLT_MIN);
	printf("-FLT_MIN: "); checkFloat(-FLT_MIN);
	printf("FLT_MAX: "); checkFloat(FLT_MAX);
	printf("-FLT_MAX: "); checkFloat(-FLT_MAX);
	
	printf("\n");
	char zeichen = 'A';
	zeichen ++;
	printf("Inhalt von zeichen: %c.\n", zeichen);
	printf("und die Anzahl der Bytes: %d.\n", sizeof(zeichen));
	
	printf("\n");
	printf("Alle Zeichen mit den Codes 0-255:\n");
	int i,j;
	for (i=0; i<8; i++) 
	{
		printf("0x%x: ", i*32);
		for (j=0; j<32; j++)
		{
			char c = i*32 + j;
			printf("%c ", c);
		}
		printf("\n");
	}
	
	return 0;
}

void checkFloat(float f)
{
	int *alsoF = &f;
	// assign a bit pattern to f:
	// *alsoF = 0x7fffffff;
	
	// überprüfen, ob die beiden Variablen wie erwartet die gleiche Adresse haben:
	// printf("&f = 0x%x\n", &f);
	// printf("alsoF = 0x%x\n", alsoF);
	// printf("\n");
	
	printf("f=%E ; *alsoF=0x%x.\n", f, *alsoF);
}

