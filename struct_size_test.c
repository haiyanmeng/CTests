#include <stdio.h>

int main() {
	int t[] = {1,2,3,4,5,6,7,8,9,10,11};
	int *s = t;
	printf("sizeof(t) = %zu\n", sizeof(t));
	printf("elements of (t) = %zu\n", sizeof(t)/sizeof(t[0]));

	printf("sizeof(s) = %zu\n", sizeof(s));
	return 0;
}

/* output:
sizeof(t) = 44
elements of (t) = 11
sizeof(s) = 8
*/

// gcc -g3 -std=c99 -pedantic -Wall struct_size_test.c
