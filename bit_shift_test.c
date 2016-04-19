#include <stdio.h>

int main(void) {
	int i = 0;
	int a = 1;
	int b = -1;
	/*
	The New C Standard 
	1185 If the value of the right operand is negative or is greater than or equal to the width of the promoted left operand, the behavior is undefined.
	*/
	for(i=0; i<100; i++) {
		printf("%d >> %d = %d\n", a, i, a>>i);
	}

	for(i=0; i<100; i++) {
		printf("%d << %d = %d\n", a, i, a<<i);
	}

	for(i=0; i<100; i++) {
		printf("%d >> %d = %d\n", b, i, b>>i);
	}

	for(i=0; i<100; i++) {
		printf("%d << %d = %d\n", b, i, b<<i);
	}
	
	return 0;
}

// gcc --std=c99 -pedantic -Wall bit_shift_test.c 
