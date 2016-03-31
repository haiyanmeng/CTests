#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int f(const char *s) {
	unsigned long r;
	char *t = NULL;

	assert(s);
	errno = 0;
	r = strtoul(s, &t, 0);
	if(errno > 0) {
		printf("strtoul(`%s`) fails: %s!\n", s, strerror(errno));
		printf("\tendptr (%p) is %s\n", (void *)&t, t);
		if(errno == ERANGE) {
			printf("%s  ==>  %lu; ULONG_MAX = %lu\n", s, r, ULONG_MAX);
		}
		return -1;
	}
	printf("%s  ==>  %lu\n", s, r);
	printf("\tendptr (%p) is %s\n", (void *)&t, t);
	return 0;
}

int main() {
	f("+245");
	f("-245");
	printf("(unsigned long) -245 = %lu\n", (unsigned long) -245);
	f("1111111111111111111111111111111111111111111111111111111111111111111111111111");
	f("123hallo");
	f("-123hallo");

	/* output:
	+245  ==>  245
	        endptr (0x7ffda02c64c0) is
	-245  ==>  18446744073709551371
	        endptr (0x7ffda02c64c0) is
	(unsigned long) -245 = 18446744073709551371
	strtoul(`1111111111111111111111111111111111111111111111111111111111111111111111111111`) fails: Numerical result out of range!
	        endptr (0x7ffda02c64c0) is
	1111111111111111111111111111111111111111111111111111111111111111111111111111  ==>  18446744073709551615; ULONG_MAX = 18446744073709551615
	123hallo  ==>  123
	        endptr (0x7ffda02c64c0) is hallo
	+123hallo  ==>  123
	        endptr (0x7ffda02c64c0) is hallo
	-123hallo  ==>  18446744073709551493
	        endptr (0x7ffda02c64c0) is hallo
	*/

	return 0;
}

// gcc -g3 -std=c99 -pedantic -Wall strtoul_test.c 


