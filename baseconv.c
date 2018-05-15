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
#include <string.h> // für strcmp()
#include "lib/baseconv.c"

void debugging(void);

int main(int argc, char *argv[]) {
	// debugging();

	if (argc < 2 || ((argc == 2) && !strcmp(argv[1], "--help"))) {
		// print usage:
		fprintf(stderr, "baseconv is simple program made for educational purposes of its\n");
		fprintf(stderr, "author. It can read and write integer numbers (in a range of \n");
		fprintf(stderr, "-2^63-1..2^63-1) in numeric symbolic notations with bases from 2..36. \n");
		fprintf(stderr, "WARNING: It does not have adequate error handling!\n\n");
		fprintf(stderr, "Usage:\n\n");
		fprintf(stderr, "baseconv <decimal number>\n");
		fprintf(stderr, "   Prints the given number in different notation systems.\n");
		fprintf(stderr, "baseconv <decimal number> <target base>\n");
		fprintf(stderr, "   Prints the given number in the notation system with the target\n");
		fprintf(stderr, "   base. Both the number and the base must be given in decimal\n");
		fprintf(stderr, "   notation.\n");
		fprintf(stderr, "baseconf <number> <base> <target base>\n");
		fprintf(stderr, "   Parses the given number in symbolic notation system with base\n");
		fprintf(stderr, "   and prints it in the notation system with target base. Both\n");
		fprintf(stderr, "   base and target base must be given in decimal notation.\n");
		fprintf(stderr, "\n");
		return 0;
	}

	initReverseCharPool(); // function in lib/baseconv.c

	if (argc == 2) {
		// nur eine Zahl wurde eingegeben -> Dezimal in mehrere:
		long int z = getNumericIntBase(argv[1], 10);

		int basen[] = {2, 3, 4, 5, 8, 10, 16, 36};
		int i;
		for (i=0; i<8; i++) {
			int basis = basen[i];
			char* bunteZahl = getSymbolicIntBase(z, basis);
			printf("%s(%d)\n", bunteZahl, basis);
		}
	} else if (argc == 3) {
		// zwei Zahlen: Dezimal in Ziel-System:
		long int z = getNumericIntBase(argv[1], 10);
		int basis = getNumericIntBase(argv[2], 10);
		printf("%s\n", getSymbolicIntBase(z, basis));
	} else if (argc == 4) {
		// drei Zahlen: Z, Basis, Ziel-Basis
		int zBasis = getNumericIntBase(argv[2], 10);
		long int z = getNumericIntBase(argv[1], zBasis);
		int basis = getNumericIntBase(argv[3], 10);
		printf("%s\n", getSymbolicIntBase(z, basis));
	}
}

void debugging(void) {
	printf("2^32= %lu\n", pow(2,32));
	printf("2^62= %lu\n", pow(2,62));
	// printf("2^63= %lu\n", pow(2,63));
	// printf("2^64= %lu\n", pow(2,64));
}

