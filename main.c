#include <stdio.h>
#include <string.h>

int ff_init(int, char**);
int ff_rect(int, char**);

int main(int argc, char* argv[]) {
	if(argc < 2) return fprintf(stderr, "Usage: ffgeom [operation] [args]\n"), -1;
	if(!strcmp(argv[1], "init"))
		return ff_init(argc-2, argv+2);
	else if(!strcmp(argv[1], "rect"))
		return ff_rect(argc-2, argv+2);
}

