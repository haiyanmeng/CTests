#include <assert.h>
#include <stdio.h>

void f(char *a) {
	if(!a) {
		printf("`%s` is NULL!\n", a);
	} else if(!a[0]) {
		printf("the first char of `%s` is null byte!\n", a);
	}
}

int main() {
	char *a = NULL;
	char *b = "";
	char *c = "hello";
	assert(c);
	assert(b);
	//assert(a);
	f(b);
	f(a);
	return 0;
}

/* output:
the first char of `` is null byte!
`(null)` is NULL!
*/

// gcc -g3 -Wall -pedantic -std=c99 assert_test.c
