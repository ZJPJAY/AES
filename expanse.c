#include "expanse.h"

void hex_array_print(uint8_t* out_print, char* dec, int out_pirint_len)
{
    printf("%s\n", dec);
	for (int i = 0; i < out_pirint_len; i++) {
		printf("%02x %02x %02x %02x ", out_print[4*i+0], out_print[4*i+1], out_print[4*i+2], out_print[4*i+3]);
	}

	printf("\n");
}

void init_file(char* file_name, uint8_t* str)
{
	//uint8_t str[16] = {0x00};
	char code = 'a';
	int i = 0;

	FILE* fd = fopen(file_name, "r");

	if(fd == NULL)
	{
		printf("Error file open!\n");
		exit(0);
	}
	
	while((code = fgetc(fd)) != EOF)
	{
		str[i++] = code;
		if(i == 16)break;
	}

	fclose(fd);
}