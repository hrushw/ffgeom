#include <stdio.h>
#include <string.h>
#include <stdint.h>

void ff_init(int, char*[]);
void ff_rect(int, char*[]);
void ff_blip(int, char*[]);
void ff_ellipse(int argc, char*[]);

int main(int argc, char* argv[]) {
	if(argc < 2) return fprintf(stderr, "Usage: ffgeom [-i file] [operation] [args]\n"), -1;

	if(!strcmp(argv[1], "init"))
		ff_init(argc-2, argv+2);
	else if(!strcmp(argv[1], "rect"))
		ff_rect(argc-2, argv+2);
	else if(!strcmp(argv[1], "blip"))
		ff_blip(argc-2, argv+2);
	else if(!strcmp(argv[1], "ellipse"))
		ff_ellipse(argc-2, argv+2);

	return 0;
}

