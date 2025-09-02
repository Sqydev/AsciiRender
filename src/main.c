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

	// Get first bytes that can contain magic numbers
	unsigned char MagicCheck[12];
	int read_bytes = fread(MagicCheck, 1, 12, file);
	if(read_bytes != 12) {
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

	// PNG
	if (!memcmp(MagicCheck, (unsigned char[]){0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A}, 8)) {
		if(debug) {printf("PNG");}
		PNG_Convert_To_Ascii(InputPath, OutputPath);
	}
	// JPG
	else if (!memcmp(MagicCheck, (unsigned char[]){0xFF, 0xD8, 0xFF, 0xE0}, 4)) {
		if(debug) {printf("JPG");}
	}
	// MP4
	else if (!memcmp(MagicCheck, (unsigned char[]){0x00, 0x00, 0x00, 0x18, 0x66, 0x74, 0x79, 0x70, 0x69, 0x73, 0x6F, 0x6D}, 12)) {
		if(debug) {printf("MP4");}
	}
	// MKV
	else if (!memcmp(MagicCheck, (unsigned char[]){0x1A, 0x45, 0xDF, 0xA3}, 4)) {
		if(debug) {printf("MKV");}
	}
	// MPEG
	else if (!memcmp(MagicCheck, (unsigned char[]){0x00, 0x00, 0x01, 0xBA}, 4)) {
		if(debug) {printf("MPEG");}
	}
	else {
		printf("Unsuported format");
	}

	fclose(file);
	return 0;
}
