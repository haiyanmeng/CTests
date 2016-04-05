#include <stdio.h>

#define print printmacro
#define concat(x,y) x##y //token concatenation: x, y will not be macro-expanded first. they are directly concatenated due to the usage of ##.
#define concat_str( x ,   y ) x y
#define concat_str1(x,y) #x #y

char *f = "%s:%s:%d: ";
#define LDEBUG(fmt, ...) printf("%s:%s:%d: " fmt, __func__, __FILE__, __LINE__, __VA_ARGS__)


void printhello() {
	fprintf(stdout, "hello!\n");
}

int main() {
	concat( print , hello )();	
	fprintf(stdout, concat_str("hello", "world!\n"));
	fprintf(stdout, concat_str1(hello, world!\n));
	LDEBUG("hello world: %s", "hmeng\n");
	return 0;
}

/* output:
hello!
helloworld!
helloworld!
main:macro_test.c:20: hello world: hmeng
*/

// gcc -g3 -std=c99 -pedantic -Wall macro_test.c 
