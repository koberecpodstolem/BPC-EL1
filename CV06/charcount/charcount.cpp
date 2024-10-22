// charcount.cpp: Definuje vstupní bod pro aplikaci.
//

#include "charcount.h"
#include <cctype>
#include "counter.h"

using namespace std;

int main()
{
	char text[] = "Toto jsou 2 vzorove vety, ktere budou zpracovavany Vasemi funkcemi. Auto Hyundai ix35 ma pres 120 konskych sil.";
	int lcc = letterCount(text);
	int dcc = digitCount(text);

	printf("V textu >"); printf(text); printf("< je:");
	printf("\nPismen: "); printf("%d", lcc);
	printf("\nCislic: "); printf("%d", dcc);
	
}
