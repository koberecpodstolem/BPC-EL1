#include <math.h>
int indexNearest(int size, int (*pointArray)[2], int referenceX, int referenceY) {
	int index = 0;
	for (int i = 0; i < size; i++) {
		int distance;
		double d = sqrt(pow((referenceX - pointArray[i][0]), 2) + pow((referenceY - pointArray[i][1]), 2));
	}
	return 0;
}

double averageDistance(int size, int (*pointArray)[2], int referenceX, int referenceY) {
	return 0;
}
