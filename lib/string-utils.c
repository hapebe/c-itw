void kuerzen(char* dest, char* src, int lMax) {
	int l = strlen(src);
	if (l < lMax) {
		// einfach kopieren:
		strcpy(dest, src);
		return;
	}

	int i;
	for (i=0; i<lMax-3; i++) {
		dest[i] = src[i];
	}
	// drei Punkte als Auslassungszeichen anhängen:
	for (; i<lMax; i++) {
		dest[i] = '.';
	}

	// und ein abschließendes NULL:
	dest[i] = '\0';
}

void rechtsAuffuellen(char* dest, char* src, int l) {
	// jedenfalls kopieren:
	strcpy(dest, src);

	int srcL = strlen(src);
	if (srcL >= l) return; // nix weiter!

	int i;
	for (i=srcL; i<l; i++) {
		dest[i] = ' ';
	}
	// und ein abschließendes NULL:
	dest[i] = '\0';
}

void linksAuffuellen(char* dest, char* src, int l) {
	// if (dest == src) die("beim Aufruf von linksAuffuellen() dürfen Ein- und Ausgabepuffer nicht identisch sein!");

	int i;

	int srcL = strlen(src);
	if (srcL >= l) {
		// nur kopieren:
		strcpy(dest, src);
		return;
	}

	int lPrefix = l-srcL;
	for (i=0; i<lPrefix; i++) {
		dest[i] = ' ';
	}
	for (i=0; i<srcL; i++) {
		dest[i+lPrefix] = src[i];
	}
	// und ein abschließendes NULL:
	dest[l] = '\0';
}

void toLowerCase(char* dest, char * src) {
	int i;
	for(i=0; i<strlen(src); i++) {
		dest[i] = src[i] | 0x20;
	}
	dest[i] = '\0';
}

// source: https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
//
// Note: This function returns a pointer to a substring of the original string.
// If the given string was allocated dynamically, the caller must not overwrite
// that pointer with the returned value, since the original pointer must be
// deallocated using the same allocator with which it was allocated.  The return
// value must NOT be deallocated using free() etc.
char *trim(char *str) {
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}
