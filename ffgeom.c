#include <stdio.h>
#include <string.h>
#include <stdint.h>

void ff_wrap_init(int, char*[]);
void ff_wrap_rect(int, char*[]);
void ff_wrap_blip(int, char*[]);
void ff_wrap_ellipse(int argc, char*[]);

int main(int argc, char* argv[]) {
	if(argc < 2) return fprintf(stderr, "Usage: ffgeom [-i file] [operation] [args]\n"), -1;

	if(!strcmp(argv[1], "init"))
		ff_wrap_init(argc-2, argv+2);
	else if(!strcmp(argv[1], "rect"))
		ff_wrap_rect(argc-2, argv+2);
	else if(!strcmp(argv[1], "blip"))
		ff_wrap_blip(argc-2, argv+2);
	else if(!strcmp(argv[1], "ellipse"))
		ff_wrap_ellipse(argc-2, argv+2);

	return 0;
}

