#include <unistd.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>

#include "ffioutil.h"
#include "ff_routines.h"

int stage0(int outfd) {
	uint8_t clr[8] = {0};
	ff_getclr("cccccc", clr);
	ff_rect(outfd, 400, 400, clr);
	close(outfd);

	wait(NULL);
	return 0;
}

int stage1(int outfd) {
	uint8_t clrs[4][8] = {{0}};
	ff_getclr("0000FF", clrs[0]);
	ff_getclr("FF0000", clrs[1]);
	ff_getclr("FFFFFF", clrs[2]);
	ff_getclr("000000", clrs[3]);

	ff_blip(outfd, 120, 120, clrs);
	close(outfd);

	wait(NULL);
	return 0;
}

int stage2(int basefd, int layerfd, int outfd) {
	ff_overlay(basefd, layerfd, outfd, 200, 200);
	close(basefd);
	close(layerfd);
	close(outfd);

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

int main(void) {
	static const char* msg_init = "Test init...\n";
	fprintf(stderr, msg_init);

	int iofd1[2];
	trypipe(iofd1);

	pid_t pid = fork();

	switch(pid) {
		case -1:
			return -1;
		case 0:
			break;
		default:
			stage0(iofd1[1]);
			return 0;
	}

	int iofd2[2];
	trypipe(iofd2);

	pid = fork();
	switch(pid) {
		case -1:
			return -1;
		case 0:
			break;
		default:
			stage1(iofd2[1]);
			return 0;
	}

	pid = fork();
	switch(pid) {
		case -1:
			return -1;
		case 0:
			 break;
		default:
			stage2(iofd1[0], iofd2[0], 1);
			return 0;
	}

	return 0;
}
