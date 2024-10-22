#include "ctype.h"

int digitCount(char string[]) {

	int dc = 0;

	const int size = sizeof(string);

	for (int i = 0; string[i] != '\0'; i++) {
		if (isdigit(string[i])) {
			dc++;
		}
	}
	return dc;
}

int letterCount(char string[]) {

	int lc = 0;

	const int size = sizeof(string);

	for (int i = 0; string[i] != '\0'; i++) {
		if (isalpha(string[i])) {
			lc++;
		}
	}
	return lc;
}
int wordCount(char string[]) {

	int wc = 1;

	const int size = sizeof(string);

	for (int i = 0; string[i] != '\0'; i++) {
		if (string[i] == ('\t' || ',' || '.')) {
			wc++;
		}
	}
	return wc;
}