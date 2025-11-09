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

	uint8_t clr[8] = FF_COLOR_BASE;
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

int layer1(int pinfd) {
	close(0);
	if(fcntl(pinfd, F_DUPFD, 0) != 0) return -1;

	int out = 0;
	uint8_t clr[8] = FF_COLOR_BASE;
	if(ff_getclr("007F3F", clr)) {
		out = -1;
		goto end;
	}
	ff_rect(40, 40, 50, 50, clr);

end:
	return out;
}

int main(void) {
	int iofd1[2];
	if(pipe(iofd1)) return -1;

	pid_t pid = fork();
	switch(pid) {
	case -1:
		return -1;
		break;

	case 0:
		return layer1(iofd1[0]);

	default:
		return layer0(iofd1[1]);
	}

	return 0;
}
