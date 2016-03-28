#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
	FILE *f = fopen(" ", "r");

	if(f)
		fclose(f);
	else
		printf("%d %s\n", errno, strerror(errno)); //output: 2 No such file or directory
	return 0;
}

// gcc -g3 -std=c99 -pedantic -Wall fopen_test.c 
