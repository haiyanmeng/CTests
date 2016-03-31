#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f(const char *s) {
	assert(s);
	unsigned long r;
	errno = 0;
	r = strtoul(s, NULL, 0);
	if(errno > 0) {
		printf("strtoul(`%s`) fails: %s!\n", s, strerror(errno));
		if(errno == ERANGE) {
			printf("%s  ==>  %lu; ULONG_MAX = %lu\n", s, r, ULONG_MAX);
		}
		return -1;
	}
	printf("%s  ==>  %lu\n", s, r);
	return 0;
}

int main() {
	f("+245");
	f("-245");
	printf("(unsigned long) -245 = %lu\n", (unsigned long) -245);
	f("1111111111111111111111111111111111111111111111111111111111111111111111111111");

	/* output:
	+245  ==>  245
	-245  ==>  18446744073709551371
	(unsigned long) -245 = 18446744073709551371
	strtoul(`1111111111111111111111111111111111111111111111111111111111111111111111111111`) fails: Numerical result out of range!
	1111111111111111111111111111111111111111111111111111111111111111111111111111  ==>  18446744073709551615; ULONG_MAX = 18446744073709551615
	*/

	return 0;
}

// gcc -g3 -std=c99 -pedantic -Wall strtoul_test.c 


