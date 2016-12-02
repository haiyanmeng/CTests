#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int set_nonblock(int fd) {
	int rc = fcntl(fd, F_GETFL);
	if(rc == -1) {
		fprintf(stderr, "fcntl(%d, F_GETFL) failed: %s\n", strerror(errno));
		return -1;
	}
	rc = fcntl(fd, F_SETFL, rc|O_NONBLOCK);
	if(rc == -1) {
		fprintf(stderr, "fcntl(%d, F_SETFL, ...) failed: %s\n", strerror(errno));
		return -1;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	const char *input;
	int rc;
	size_t len;
	pid_t child = -1;
	int in[2] = {-1, -1};
	int out[2] = {-1, -1};
	int err[2] = {-1, -1};
	
	if(argc != 2) {
		fprintf(stderr, "there should have two arguments!\n");
		exit(EXIT_FAILURE);
	}

	input = argv[1];	
	len = (size_t)snprintf(NULL, 0, "%s", input);

	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	if(pipe(in) == -1) {
		fprintf(stderr, "`pipe(in)` failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(pipe(out) == -1) {
		fprintf(stderr, "`pipe(out)` failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(pipe(err) == -1) {
		fprintf(stderr, "`pipe(err)` failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	switch(child = fork()) {
	case -1: // error
		fprintf(stderr, "`fork()` failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	case 0: // child
		fprintf(stdout, "child pid: %ld, child ppid: %ld\n", (long) getpid(), (long)getppid());
		fprintf(stdout, "child process pipe in read end %d, write end: %d\n", in[0], in[1]);
		fprintf(stdout, "child process pipe out read end %d, write end: %d\n", out[0], out[1]);
		fprintf(stdout, "child process pipe err read end %d, write end: %d\n", err[0], err[1]);

		if(close(in[1])) {
			fprintf(stderr, "`close(in[1])` failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if(close(out[0])) {
			fprintf(stderr, "`close(out[0])` failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if(close(err[0])) {
			fprintf(stderr, "`close(err[0])` failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if(dup2(in[0], STDIN_FILENO) == -1) {
			fprintf(stderr, "`dup2(in[0], STDIN_FILENO)` failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if(dup2(out[1], STDOUT_FILENO) == -1) {
			fprintf(stderr, "`dup2(out[1], STDOUT_FILENO)` failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		if(dup2(err[1], STDERR_FILENO) == -1) {
			fprintf(stderr, "`dup2(err[1], STDERR_FILENO)` failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if(close(in[0])) {
			fprintf(stderr, "`close(in[0])` failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if(close(out[1])) {
			fprintf(stderr, "`close(out[1])` failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if(close(err[1])) {
			fprintf(stderr, "`close(err[1])` failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		execlp("sh", "sh", "-c", "wc", (char *)NULL);
		fprintf(stderr, "child process `wc`, failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	// parent
	fprintf(stdout, "parent pid: %ld, parent ppid: %ld\n", (long) getpid(), (long)getppid());
	fprintf(stdout, "parent process pipe in read end %d, write end: %d\n", in[0], in[1]);
	fprintf(stdout, "parent process pipe out read end %d, write end: %d\n", out[0], out[1]);
	fprintf(stdout, "parent process pipe err read end %d, write end: %d\n", err[0], err[1]);

	if(close(in[0])) {
		fprintf(stderr, "`close(in[0])` failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(close(out[1])) {
		fprintf(stderr, "`close(out[1])` failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(close(err[1])) {
		fprintf(stderr, "`close(err[1])` failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if(set_nonblock(in[1])) exit(EXIT_FAILURE);
	if(set_nonblock(out[0])) exit(EXIT_FAILURE);
	if(set_nonblock(err[0])) exit(EXIT_FAILURE);

	while(1) {
		char output[100], error_data[100];
		size_t len_out = 100, len_err = 100;
		pid_t pid;
		int status;
		ssize_t r;

		if(len == 0 && in[1] > 0) {
			if(close(in[1])) {
				fprintf(stderr, "parent close(in[1]) failed: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}

			in[1] = -1;
		}

		pid = waitpid(child, &status, WNOHANG);

		if(pid == -1) {
			fprintf(stderr, "`waitpid` failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if(len) {
			r = write(in[1], input, len);
			if(r == -1) {
				if(errno == EPIPE) {
					fprintf(stdout, "the child process closed its read end, the parent process can not send data!\n");
					len = 0;
				}
				if(errno != EAGAIN && errno != EINTR) {
					fprintf(stderr, "`write(in[1], ...)` failed: %s\n", strerror(errno));
					exit(EXIT_FAILURE);
				}
			} else {
				input += (size_t)r;
				len -= (size_t)r;
			}
		}

		r = read(out[0], output, len_out);
		if(r == -1) {
			if(errno != EAGAIN && errno != EINTR) {
				fprintf(stderr, "`read(out[0], ...)` failed: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
		} else if(r > 0){
			output[r] = '\0';
			fprintf(stdout, "the output of child process (size %d):\n%s", (int)r, output);
		}

		r = read(err[0], error_data, len_err);
		if(r == -1) {
			if(errno != EAGAIN && errno != EINTR) {
				fprintf(stderr, "`read(err[0], ...)` failed: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
		} else if(r > 0){
			error_data[r] = '\0';
			fprintf(stderr, "the error of child process (size %d):\n%s", (int)r, error_data);
		}

		if(pid == child) break;
	}

	if(in[1] >= 0) close(in[1]);
	if(out[0] >= 0) close(out[0]);
	if(err[0] >= 0) close(err[0]);

	return 0;
}

