#include "png.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void BadUsageMessage() {
	printf("BAD USAGE MESSAGE HERE");
}

void HelpMessage() {
	printf("HELP MESSAGE HERE");
}

int main(int argc, char *argv[]) {
	bool debug = false;
	char *InputPath = NULL;
	char *OutputPath = NULL;

	for (int i = 1; i < argc; i++) {
        // Get input arg
		if (!strcmp(argv[i], "--input")) {
            InputPath = argv[i + 1];
			break;
        } else {
			BadUsageMessage();
			return 1;
		}

		// Get output arg
        if (!strcmp(argv[i], "--output")) {
            OutputPath = argv[i + 1];
			break;
        } else {
			BadUsageMessage();
			return 1;
		}

		// Do debuging
		if (!strcmp(argv[i], "--debug")) {
            debug = true;
			break;
        }
		// HELP!
		if (!strcmp(argv[i], "--help")) {
            HelpMessage();
			return 0;
        }
    }

	FILE *file = fopen(InputPath, "rb");
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
		PNG_Convert_To_Ascii(InputPath, OutputPath);
	}

	fclose(file);
	return 0;
}
