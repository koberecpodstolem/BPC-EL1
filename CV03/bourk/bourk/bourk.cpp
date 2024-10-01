// bourk.cpp: Definuje vstupní bod pro aplikaci.
//

#include "bourk.h"

using namespace std;

int main()
{
	int speed_of_sound = 340;
	int time;
	printf("Insert time in  seconds: ");
	cin >> time;
	int distance = speed_of_sound * time;
	printf("The storm is ");
	printf("%d", distance);
	printf(" meters away");
	return 0;
}
