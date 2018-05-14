#include <stdio.h>

#define DUMP_LINEWIDTH 16

/**
 * dumps the contents of the argument as plain text and as hex, with a pre-specified length (i.e. not null-terminated!)
 */
void dumpL(char* text, int length) {
	// how many lines will we print?
	int nLines = length / DUMP_LINEWIDTH;
	if (length % DUMP_LINEWIDTH != 0) nLines++; // if we have a fraction of chars for the last line, we should still include it.

	int row, col, cursor;
	for (row=0; row<nLines; row++) {
		// print plain text
		for (col=0; col<DUMP_LINEWIDTH; col++) {
			cursor = row*DUMP_LINEWIDTH + col;
			if (cursor < length) {
				printf("%c", text[cursor]);
			} else {
				printf(" ");
			}
		}
		// print separator:
		printf("\t");
		// print hex dump
		for (col=0; col<DUMP_LINEWIDTH; col++) {
			cursor = row*DUMP_LINEWIDTH + col;
			if (cursor < length) {
				printf("%2x ", text[cursor] & 0x000000FF);
			} else {
				printf("   ");
			}
		}
		printf("\n");
	}
}

/**
 * dumps the contents of the argument as plain text and as hex.
 */
void dump(char* text) {
	// first, let's find out how long our string is:
	char* end = text; // printf("End ist: %c\n", *end);
	while(*end != '\0')	end ++;
	int length = end - text + 1;
		// printf("I got a text with length %d.\n", length); return;

	dumpL(text, length);
}
