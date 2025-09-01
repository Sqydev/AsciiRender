#include "png.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char *argv[]) {
	bool debug = false;

	for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--debug") == 0) {
            debug = true;
        }
    }

	FILE *file = fopen(argv[1], "rb");
	if(!file) {
		printf("Failed to open file");
		return 1;
	}

	unsigned char MagicCheck[8];
	int read_bytes = fread(MagicCheck, 1, 8, file);
	if(read_bytes != 8) {
		fclose(file);
		printf("Failed to open read magic number");
		return 1;
	}


	if(debug) {
		// Print magic number's
		for(int i = 0; i < read_bytes; i++) {
			printf("%02X ", MagicCheck[i]);
		}
	}

	if (!memcmp(MagicCheck, (unsigned char[]){0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}, 8)) {
		printf("PNG ");
	}

	fclose(file);
	return 0;
}
