#include <stdio.h>

void f(const char *arr) {
	arr += 2;
	printf("%s\n", arr);
}

int main() {
	char arr[10] = "hello,mhy!";
	printf("%s\n", arr);
	f(arr);
	printf("%s\n", arr);

	/* output:
	hello,mhy!
	llo,mhy!
	hello,mhy!
	*/

	return 0;
}

// gcc -g3 -std=c99 -pedantic -Wall array_name_test.c
