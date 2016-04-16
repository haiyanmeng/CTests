#include <stdio.h>
#include <string.h>

struct S1 {
	char *s;
	int i;
};

char str[6] = "h\0llo\0";

char str1[] = "hello";

int main(void) {
	static struct S1 a[] = {
		{"abcd", 1},
		{"efgh", 2}
	};

	struct S1 *p = a;

	printf("%s\n", str);

	char str[] = "hello";
	fprintf(stdout, "str: %s; sizeof(char): %zu; sizeof(str): %zu; strlen(str):  %zu\n", str, sizeof(char), sizeof(str), strlen(str));

	char str1[8] = "hello";
	fprintf(stdout, "str1: %s; sizeof(char): %zu; sizeof(str1): %zu; strlen(str1):  %zu\n", str, sizeof(char), sizeof(str1), strlen(str1));

	char str2[5] = "hello";
	fprintf(stdout, "str2: %s; sizeof(char): %zu; sizeof(str2): %zu; strlen(str2):  %zu\n", str, sizeof(char), sizeof(str2), strlen(str2));
	// strlen(str2) has a memory leakage: Conditional jump or move depends on uninitialised value

	char str3[5] = "hello";
	fprintf(stdout, "str3: %s; sizeof(char): %zu; sizeof(str3): %zu;\n", str, sizeof(char), sizeof(str3));

	printf("%s\n", p->s); 
	printf("%s\n", p[0].s); /* (*(p+0)).s */
	
	int b[3][3] = { {1,2,3}, {4,5,6}, {7,8,9}};

	int *p2 = b[0];
	int *p3 = b[1];
	int *p4 = b[2];
	int *p1[3] = {p2, p3, p4};
	printf("%d\n", p1[2][0]);

	int (*p5)[3][3] = &b;
	printf("%d\n", (*p5)[2][0]);

	return 0;
}

/* output:
h
str: hello; sizeof(char): 1; sizeof(str): 6; strlen(str):  5
str1: hello; sizeof(char): 1; sizeof(str1): 8; strlen(str1):  5
str2: hello; sizeof(char): 1; sizeof(str2): 5; strlen(str2):  5
str3: hello; sizeof(char): 1; sizeof(str3): 5;
abcd
abcd
7
7
*/

// gcc -g3 -std=c99 -pedantic -Wall strlen_test.c
