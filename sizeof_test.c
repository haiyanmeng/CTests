#include <stdio.h>
#include <string.h>

int main() {
	char a[] = "hello";
	// ouput: strlen = 5; sizeof = 6
	printf("strlen = %zu; sizeof = %zu\n", strlen(a), sizeof(a)); 
}

// gcc -g3 -std=c99 -pedantic -Wall sizeof_test.c
