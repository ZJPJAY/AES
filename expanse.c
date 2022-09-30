#include <stdint.h>

void hex_array_print(uint8_t* out_print, char* dec, int out_pirint_len)
{
    printf("%s\n", dec);
	for (int i = 0; i < out_pirint_len; i++) {
		printf("%02x %02x %02x %02x ", out_print[4*i+0], out_print[4*i+1], out_print[4*i+2], out_print[4*i+3]);
	}

	printf("\n");
}

