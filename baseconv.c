/*
 * baseconv.c
 *
 * 2018 Hans-Peter Bergner <hapebe@gmx.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <stdio.h>
#include <string.h> // for strcmp()
#include <unistd.h> // for getopt()
#include "lib/baseconv.c"
// #include "lib/dump.c" // debug output char-Arrays using dump(char[]);


void usage() {
	fprintf(stderr, "baseconv is a simple program made for educational purposes of its\n");
	fprintf(stderr, "author. It can read and write integer numbers (in a range of \n");
	fprintf(stderr, "-2^63-1..2^63-1) in numeric symbolic notations with bases from 2..36. \n");
	fprintf(stderr, "WARNING: It does not have adequate error handling!\n\n");
	fprintf(stderr, "Usage:\n\n");
	fprintf(stderr, "baseconv [-h] <decimal number>\n");
	fprintf(stderr, "   Prints the given number in different notation systems.\n");
	fprintf(stderr, "baseconv [-h] <number> <base>\n");
	fprintf(stderr, "   Parses the given number in symbolic notation system with base\n");
	fprintf(stderr, "   and prints it in different notation systems. The base must be\n");
	fprintf(stderr, "   given in decimal notation.\n");
	fprintf(stderr, "baseconf [-h] <number> <base> <target base>\n");
	fprintf(stderr, "   Parses the given number in symbolic notation system with base\n");
	fprintf(stderr, "   and prints it in the notation system with target base. Both\n");
	fprintf(stderr, "   base and target base must be given in decimal notation.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "   -h   human-readable output: adds group separators to the number\n");
	fprintf(stderr, "        output\n");
	fprintf(stderr, "\n");
}

// can be altered via command line option "-h"
int useDigitGrouping = 0;

void debugging(void);

void groupDigits(char* source, char* dest, int groupSize) {

	int sourceLength = strlen(source);
		// dumpL(source, sourceLength + 1);

	int isNegative = (source[0] == '-');

	int writeCursor = 0;
	dest[writeCursor] = '\0'; // 0-terminated string...
	writeCursor ++;

	// we start at the last digit of the source:
	int readCursor;
	int groupCount = 0;
	for (readCursor=sourceLength-1; readCursor>=0; readCursor--) {
		dest[writeCursor] = source[readCursor];

		groupCount ++;
		// readCursor > (isNegative?1:0) is for: don't use a separator in front of the first digit for positive numbers, or behind the '-' sign for negative numbers
		if (groupCount == groupSize && readCursor > (isNegative?1:0)) {
			writeCursor++;
			dest[writeCursor] = '.';
			groupCount = 0;
		}

		writeCursor++;
	}
		// dumpL(dest, sourceLength + 2);


	// now, flip dest:
	int destLength = writeCursor; // the string length, including the \0 terminus
		// printf("destLength = %d\n", destLength);
	int i=0;
	for (i=0; i<destLength/2; i++) {
		// swap [i]<->[destLength-i-1]
			// printf("Swap [%d] and [%d]...\n", i, destLength-i-1);

		int tmp = dest[i];
		dest[i] = dest[destLength-i-1];
		dest[destLength-i-1] = tmp;

		// debug: dump flipped dest[]:
			// dumpL(dest, destLength);
	}
	// debug: dump flipped dest[]:
		// printf("Final:\n"); dump(dest);

	// done - no return value
}

/*
 * removes everything but a leading '-' and "digits" from the source string and copies it to dest accordingly
 */
void ungroupDigits(char* source, char* dest) {
	int sourceLength = strlen(source); // printf("Input length: %d\n", sourceLength);
	int writeCursor = 0;
	int i;
	for (i=0; i<sourceLength; i++) {
		if (
			(i==0 && source[i] == '-') // a leading '-'
			|| (source[i] >= 48 && source[i] <= 57) // is a digit
			|| (source[i] >= 97 && source[i] <= 122) // is a lower-case letter
			|| (source[i] >= 65 && source[i] <= 90) // is an upper-case letter
		) {
			dest[writeCursor] = source[i];
			writeCursor ++;
		} else {
			; // ignore & drop this character!
		}
	}
	dest[writeCursor] = '\0'; // 0-terminated string
}

/**
 * does all the formatting for a long int in a certain symbol system,
 * and finally prints it to stdout
 */
void prettyPrint(long int zahl, int basis, int includeSuffix) {
	char out[MAX_LENGTH*2]; // allow space for digit grouping...
	char* finalString = &out[0];

	if (useDigitGrouping) { // "global" option, set via command line arg
		int groupSize = 3;
		if (basis == 2 || basis == 4 || basis == 8 || basis == 16) groupSize = 4;
		groupDigits(getSymbolicIntBase(zahl, basis), finalString, groupSize);
	} else {
		finalString = getSymbolicIntBase(zahl, basis);
	}

	if (includeSuffix) {
		printf("%s(%d)\n", finalString, basis);
	} else {
		printf("%s\n", finalString);
	}
}



int main(int argc, char *argv[]) {
	// debugging();

	// check for command line options:
	int optionCount = 0;
	int result = getopt(argc, argv, "h?0123456789");
	if (result != -1) {
		optionCount ++;
		switch((char)result) {
			case '-':
				break; // simply ignore...
			case 'h':
				useDigitGrouping = -1;
				break;
			case '?':
				usage();
				return 0;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				// no, this is a negativ number instead:
				optionCount --;
				break;
			default:
				fprintf(stderr, "Unrecognized option '%c'\n", result);
		}
	}

	// optionCount holds the number of command line args starting with "-",
	// while paramCount holds the number of args NOT starting with "-".
	int paramCount = argc -1 -optionCount;
	char* params[paramCount];
	params[0] = argv[0];
	int i;
	for (i=1; i<=paramCount; i++) {
		params[i] = argv[i+optionCount];
	}
		// for (i=0; i<=paramCount; i++) printf("[%d] = %s\n", i, params[i]);

	if (paramCount < 1 || ((argc == 2) && !strcmp(argv[1], "--help"))) {
		// print usage:
		usage();
		return 0;
	}

	initReverseCharPool(); // function in lib/baseconv.c

	// we already made sure we have at least one parameter
	// support for grouped numbers: sanitize the first parameter:
	char cleanDigits[MAX_LENGTH * 2];
	ungroupDigits(params[1], cleanDigits);
		// dump(cleanDigits);

	if (paramCount == 1) {
		// nur eine Zahl wurde eingegeben -> Dezimal in mehrere:
		long int z = getNumericIntBase(cleanDigits, 10);

		int basen[] = {2, 3, 4, 5, 8, 10, 16, 36};
		int i;
		for (i=0; i<8; i++) {
			int basis = basen[i];
			if (basis == 10) continue;
			prettyPrint(z, basis, -1); // -1 for: include suffix
		}

	} else if (paramCount == 2) {
		// zwei Zahlen: ein System in mehrere:
		int zBasis = getNumericIntBase(params[2], 10);
		long int z = getNumericIntBase(cleanDigits, zBasis);

		int basen[] = {2, 3, 4, 5, 8, 10, 16, 36};
		int i;
		for (i=0; i<8; i++) {
			int basis = basen[i];
			// if (basis == zBasis) continue;
			prettyPrint(z, basis, -1); // -1 for: include suffix
		}
	} else if (paramCount == 3) {
		// drei Zahlen: Z, Basis, Ziel-Basis
		int zBasis = getNumericIntBase(params[2], 10);
		long int z = getNumericIntBase(cleanDigits, zBasis);
		int basis = getNumericIntBase(params[3], 10);

		prettyPrint(z, basis, 0); // 0 for: don't include suffix
	}
}

void debugging(void) {
	printf("2^32= %lu\n", pow(2,32));
	printf("2^62= %lu\n", pow(2,62));
	// printf("2^63= %lu\n", pow(2,63));
	// printf("2^64= %lu\n", pow(2,64));
}

