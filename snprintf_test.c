#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char *s = "hello, world!";
	char *t = malloc(6*sizeof(char));
	int a;
	
	printf("s = `%s`; sizeof(s) = %zu; strlen(s) = %zu\n", s, sizeof(s), strlen(s));
	printf("sizeof(t) = %zu; strlen(t) = %zu\n", sizeof(t), strlen(t));
	a = snprintf(t, (size_t)5, "%s", s);
	printf("a = %d\n", a);
	printf("t = `%s`\n", t);
	printf("sizeof(t) = %zu; strlen(t) = %zu\n", sizeof(t), strlen(t));
	return 0;
}

/* output:
s = `hello, world!`; sizeof(s) = 8; strlen(s) = 13
sizeof(t) = 8; strlen(t) = 0
a = 13
t = `hell`
sizeof(t) = 8; strlen(t) = 4
*/

// gcc -g3 -std=c99 -pedantic -Wall snprintf_test.c 

