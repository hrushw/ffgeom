#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>

#include "ffioutil.h"
#include "ff_routines.h"

/* File descriptor registers to allow single function prototype for all stages */
int fds[16] = {
	-1, -1, -1, -1,
	-1, -1, -1, -1,
	-1, -1, -1, -1,
	-1, -1, -1, -1,
};

int stage0(void) {
	uint8_t clr[8] = {0};
	ff_getclr("cccccc", clr);
	ff_rect(fds[0], 400, 400, clr);
	close(fds[0]);

	wait(NULL);
	return 0;
}

int stage1(void) {
	uint8_t clrs[4][8] = {{0}};
	ff_getclr("0000FF", clrs[0]);
	ff_getclr("FF0000", clrs[1]);
	ff_getclr("FFFFFF", clrs[2]);
	ff_getclr("000000", clrs[3]);

	ff_blip(fds[0], 120, 120, clrs);
	close(fds[0]);

	wait(NULL);
	return 0;
}

int stage2(void) {
	ff_overlay(fds[0], fds[1], fds[2], 200, 200);
	close(fds[1]);
	close(fds[2]);
	close(fds[0]);

	wait(NULL);
	return 0;
}

void trypipe(int pfd[2]) {
	static const char* msg_pipe_fail = "ERROR: Pipe creation failed!\n";
	static const char* msg_pipe_success = "Pipe created...\n";

	if(pipe(pfd)) {
		fprintf(stderr, msg_pipe_fail);
		exit(EXIT_FAILURE);
	} else
		fprintf(stderr, msg_pipe_success);
}

void forkoff(int (*offstage)(void)) {
	pid_t pid = fork();
	switch(pid) {
		case -1:
			exit(EXIT_FAILURE);
		case 0:
			break;
		default:
			offstage();
			exit(EXIT_SUCCESS);
	}
}

int main(void) {
	static const char* msg_init = "Test init...\n";
	fprintf(stderr, msg_init);

	int iofd1[2];
	int iofd2[2];

	trypipe(iofd1);
	trypipe(iofd2);

	fds[0] = iofd1[1];
	forkoff(stage0);

	fds[0] = iofd2[1];
	forkoff(stage1);

	fds[0] = 1;
	fds[1] = iofd1[0];
	fds[2] = iofd2[0];
	forkoff(stage2);

	return 0;
}
