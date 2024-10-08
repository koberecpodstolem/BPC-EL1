// LeapYCheck.cpp: Definuje vstupní bod pro aplikaci.
//

#include "LeapYCheck.h"
#include "isLeap.h"

using namespace std;

int main()
{
	printf("1000   ");
	printf("%d", isLeap(1000));

	printf("\n2000   ");
	printf("%d", isLeap(2000));

	printf("\n2002   ");
	printf("%d", isLeap(2002));

	printf("\n2012   ");
	printf("%d", isLeap(2012));

	printf("\n2022   ");
	printf("%d", isLeap(2022));

	printf("\n2200   ");
	printf("%d", isLeap(2200));
}
