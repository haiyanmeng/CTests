#include <stdio.h>
#include <limits.h>

void f(long x) {
	if((long)(int)x != x) {
		printf("%ld is out of the [INT_MIN, INT_MAX]!\n", x);
	}
}

int main() {
	long x = 2347483647;
	long y = 2047483647;
	printf("NAME_MAX: %d\n", NAME_MAX);
	printf("INT_MAX: %d\n", INT_MAX);
	printf("INT_MIN: %d\n", INT_MIN);
	printf("UINT_MAX: %u\n", UINT_MAX);
	printf("x=%ld; (int)x=%d; (long)(int)x=%ld\n", x, (int)x, (long)(int)x); 
	f(x);
	printf("y=%ld; (int)y=%d; (long)(int)y=%ld\n", y, (int)y, (long)(int)y); 
	f(y);
	return 0;
}

/* output:
NAME_MAX: 255
INT_MAX: 2147483647
INT_MIN: -2147483648
UINT_MAX: 4294967295
x=2347483647; (int)x=-1947483649; (long)(int)x=-1947483649
2347483647 is out of the [INT_MIN, INT_MAX]!
y=2047483647; (int)y=2047483647; (long)(int)y=2047483647
*/

// gcc -g3 -Wall -pedantic limits_test.c
// NAME_MAX is not c99.
