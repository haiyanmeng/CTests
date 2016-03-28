#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

/* realpath does not care whether the path exists or not. */
int main() {
	char p2[PATH_MAX]; // PATH_MAX does not conform to c99, is a POSIX feature.
	/* output: 
	(null) /usr/bana 0 Success
	/home/hmeng/c/systemd /home/hmeng/c/systemd 2 No such file or directory
	(null) /home/hmeng/c/mytest/1.c 2 No such file or directory
	(null) /home/hmeng/c/mytest/dir1 20 Not a directory
	*/
	printf("%s %s %d %s\n", realpath("/usr/bana////", p2), p2, errno, strerror(errno));
	printf("%s %s %d %s\n", realpath("../systemd/////", p2), p2, errno, strerror(errno));
	printf("%s %s %d %s\n", realpath("./1.c/file1/////", p2), p2, errno, strerror(errno));
	printf("%s %s %d %s\n", realpath("dir1/dir2/file2/////", p2), p2, errno, strerror(errno));

	return 0;
}

// gcc -g3 -pedantic -Wall realpath_test.c
// -std=c99 is not used here: PATH_MAX does not conform to c99, is a POSIX feature.
