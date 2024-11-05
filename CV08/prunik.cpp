// prunik.cpp: Definuje vstupní bod pro aplikaci.
//

#include "prunik.h"
#include "praz.h"

using namespace std;

int main()
{
	double i1;
	double s1;
	double i2;
	double s2;
	double ri;
	double rs;

	printf("Zacatek 1. intervalu: ");
	scanf("%f", &i1);

	printf("Konec 1. intervalu: ");
	scanf("%f", &s1);

	printf("Zacatek 2. intervalu: ");
	scanf("%f", &i2);

	printf("Konec 2. intervalu: ");
	scanf("%f", &s2);

	int hasinte = intersection(i1, s1, i2, s2, &ri, &rs);
	printf("%d", hasinte);
}
