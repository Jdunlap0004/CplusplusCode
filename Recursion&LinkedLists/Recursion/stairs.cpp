#include "stairs.hpp"
#include <iostream>

int ways_to_top(int n) {
	int ways;

	//base cases
	if (n == 1) {return 1;}
	if (n == 2) {return 2;}
	if (n == 3) {return 4;}

	ways = ways_to_top(n - 1) + ways_to_top(n - 2) + ways_to_top(n - 3);

	return ways;
}
