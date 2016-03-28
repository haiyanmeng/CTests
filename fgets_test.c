#include <stdio.h>
#include <limits.h>
#include <unistd.h>


int main() {
	char line[LINE_MAX];
	FILE *f = fopen("fgets_testfile", "r");

	/* LINE_MAX: 2048
	 * sysconf(_POSIX2_LINE_MAX): 18446744073709551615
	 */
	printf("LINE_MAX: %d\n", LINE_MAX);
	printf("sysconf(_POSIX2_LINE_MAX): %lu\n", sysconf(_POSIX2_LINE_MAX));

	// at most 2047 characters can be read into line.	
	fgets(line, sizeof(line), f);
	printf("%s", line);
	fclose(f);
	putchar('\n');

	/* PATH_MAX: 4096
	 * pathconf(_POSIX_PATH_MAX): 18446744073709551615
	 */
	printf("PATH_MAX: %d\n", PATH_MAX);
	printf("pathconf(_POSIX_PATH_MAX): %lu\n", sysconf(_POSIX_PATH_MAX));

	return 0;
}

// gcc -g3 -pedantic -Wall fgets_test.c
// LINE_MAX and PATH_MAX are not c99, but are POSIX features.
