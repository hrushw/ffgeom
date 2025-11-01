#include <stdio.h>
#include <string.h>
#include <stdint.h>

enum e_ff_max_inputs { FF_MAX_INPUTS = 8 };
uint8_t ff_inputs_num = 0;
FILE* ff_inputs[FF_MAX_INPUTS] = {0};

int ff_init(int, char*[]);
int ff_rect(int, char*[]);
int ff_blip(int, char*[]);
int ff_ellipse(int argc, char*[]);

int main(int argc, char* argv[]) {
argeval:
	if(argc < 2) return fprintf(stderr, "Usage: ffgeom [-i file] [operation] [args]\n"), -1;

	if(!strcmp(argv[1], "-i")) {
		if(ff_inputs_num >= FF_MAX_INPUTS) return fprintf(stderr, "ERROR: Too many input files!\n"), -1;
		FILE* f = fopen(argv[2], "rb");
		if(!f) return fprintf(stderr, "ERROR: Unable to open file '%s'\n", argv[2]), -1;
		ff_inputs[ff_inputs_num] = f;
		ff_inputs_num ++;
		argc -= 2; argv += 2;
		goto argeval;
	}
	else if(!strcmp(argv[1], "init"))
		return ff_init(argc-2, argv+2);
	else if(!strcmp(argv[1], "rect"))
		return ff_rect(argc-2, argv+2);
	else if(!strcmp(argv[1], "blip"))
		return ff_blip(argc-2, argv+2);
	else if(!strcmp(argv[1], "ellipse"))
		return ff_ellipse(argc-2, argv+2);
}

