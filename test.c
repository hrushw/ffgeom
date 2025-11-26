#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "ffioutil.h"
#include "ff_routines.h"

int layer0(int poutfd) {
	close(1);
	if(fcntl(poutfd, F_DUPFD, 1) != 1) return -1;

	int out = 0;

	uint8_t clr[8] = {0};
	if(ff_getclr("7f0000", clr)) {
		out = -1;
		goto end;
	}

	ff_init(200, 200, clr);

	int chldout = 0;
end:
	wait(&chldout);
	return out ? out : chldout;
}

int layer1(int pinfd, int poutfd) {
	close(0);
	if(fcntl(pinfd, F_DUPFD, 0) != 0) return -1;

	close(1);
	if(fcntl(poutfd, F_DUPFD, 1) != 1) return -1;

	int out = 0;
	uint8_t clr[8] = {0};
	if(ff_getclr("007F3F", clr)) {
		out = -1;
		goto end;
	}
	ff_rect(40, 40, 50, 50, clr);

	int chldout = 0;
end:
	wait(&chldout);
	return out;
}

int layer2(int pinfd) {
	close(0);
	if(fcntl(pinfd, F_DUPFD, 0) != 0) return -1;

	int out = 0;
	uint8_t clr[8] = {0};
	if(ff_getclr("7f007f", clr)) {
		out = -1;
		goto end;
	}
	ff_ellipse(120, 120, 20, 40, clr);

end:
	return out;
}

int main(void) {
	int iofd1[2];
	if(pipe(iofd1)) return -1;
	int iofd2[2];
	if(pipe(iofd2)) return -1;

	pid_t pid = fork();
	switch(pid) {
	case -1:
		return -1;

	case 0:
		break;

	default:
		return layer0(iofd1[1]);
	}
	/* Pipeline continues to second layer */

	pid = fork();
	switch(pid) {
	case -1:
		return -1;

	case 0:
		break;

	default:
		return layer1(iofd1[0], iofd2[1]);
	}

	layer2(iofd2[0]);

	return 0;
}
