#include "expanse.h"
#include "aes.h"

/*
* Appendix A - Key Expansion Examples
*/
	
/* 128 bits */
/* uint8_t key[] = {
	0x2b, 0x7e, 0x15, 0x16,
	0x28, 0xae, 0xd2, 0xa6,
	0xab, 0xf7, 0x15, 0x88,
	0x09, 0xcf, 0x4f, 0x3c};
	
/* 192 bits */
/* uint8_t key[] = {
	0x8e, 0x73, 0xb0, 0xf7,
	0xda, 0x0e, 0x64, 0x52,
	0xc8, 0x10, 0xf3, 0x2b,
	0x80, 0x90, 0x79, 0xe5,
	0x62, 0xf8, 0xea, 0xd2,
	0x52, 0x2c, 0x6b, 0x7b}; */

/* 256 bits */
/* uint8_t key[] = {
	0x60, 0x3d, 0xeb, 0x10,
	0x15, 0xca, 0x71, 0xbe,
	0x2b, 0x73, 0xae, 0xf0,
	0x85, 0x7d, 0x77, 0x81,
	0x1f, 0x35, 0x2c, 0x07,
	0x3b, 0x61, 0x08, 0xd7,
	0x2d, 0x98, 0x10, 0xa3,
	0x09, 0x14, 0xdf, 0xf4};
*/

/* uint8_t in[] = {
	0x32, 0x43, 0xf6, 0xa8,
	0x88, 0x5a, 0x30, 0x8d,
	0x31, 0x31, 0x98, 0xa2,
	0xe0, 0x37, 0x07, 0x34}; // 128
*/

/*
* Appendix C - Example Vectors
*/

/* 128 bit key */
uint8_t key[] = {
	0x00, 0x01, 0x02, 0x03, 
	0x04, 0x05, 0x06, 0x07, 
	0x08, 0x09, 0x0a, 0x0b, 
	0x0c, 0x0d, 0x0e, 0x0f};

/* 192 bit key */
/* uint8_t key[] = {
	0x00, 0x01, 0x02, 0x03,
	0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13,
	0x14, 0x15, 0x16, 0x17}; */

/* 256 bit key */
/* uint8_t key[] = {
	0x00, 0x01, 0x02, 0x03,
	0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13,
	0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1a, 0x1b,
	0x1c, 0x1d, 0x1e, 0x1f}; */

/* uint8_t in[] = {
	0x00, 0x11, 0x22, 0x33,
	0x44, 0x55, 0x66, 0x77,
	0x88, 0x99, 0xaa, 0xbb,
	0xcc, 0xdd, 0xee, 0xff}; */


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

int encode_file_get(FILE* fd_get, uint8_t* str)
{
	int check_EOF = 0;

	for(int i = 0; i < 16; i++)
	{
		if((check_EOF = fgetc(fd_get)) == EOF)
		{
			if(i == 0)
			{
				return -1;
			}
			
			for(i; i < 16; i++)
			{
				str[i] = 255;
			}
			return 0;
		}
		
		str[i] = (uint8_t)check_EOF;
	}

	return 1;
}

int decode_file_get(FILE* fd_get, uint8_t* str)
{
	int check_EOF = 0;

	for(int i = 0; i < 16; i++)
	{
		if((check_EOF = fgetc(fd_get)) == EOF)
		{
			str[i-1] = 255;

			return -1;
		}
		str[i] = (uint8_t)check_EOF;
	}

	return 1;
}

void encode_file_printf(FILE* fd_put, uint8_t* str)
{
	for(int i = 0; i < 16; i++)
	{
		if(fputc(str[i], fd_put) == EOF)
		{
			printf("Error file input!\n");
			exit(0);
		}
	}
}

void decode_file_printf(FILE* fd_put, uint8_t* str)
{
	int stop_input_locate_num = 15;

	for(; stop_input_locate_num > 0; stop_input_locate_num--)
	{
		if(str[stop_input_locate_num] != 255)
		{
			stop_input_locate_num++;
			break;
		}
	}

	for(int i = 0; i < 16; i++)
	{
		if(i == stop_input_locate_num)
		{
			break;
		}

		if(fputc(str[i], fd_put) == EOF)
		{
			printf("Error file input!\n");
			exit(0);
		}
	}
}

void encode_circle(char* file_name_get, char* file_name_put)
{
	FILE* fd_get = fopen(file_name_get, "r");
	FILE* fd_put = fopen(file_name_put, "w");

	uint8_t *expanded_key; // expanded key
	expanded_key = aes_init(sizeof(key));
	aes_key_expansion(key, expanded_key);

	if(fd_get == NULL)
	{
		printf("Error file open!\n");
		exit(0);
	}

	clock_t s, e;
	s = clock();

	for(;;)
	{
		uint8_t code_in[16] = {'\n'};
		uint8_t code_out[16] = {'\n'};
		int k = encode_file_get(fd_get, code_in);
		if(k == -1)break;

		hex_array_print(code_in, "Plaintext message:", 4);

		aes_cipher(code_in, code_out, expanded_key);

		hex_array_print(code_out, "Ciphered message:", 4);

		encode_file_printf(fd_put, code_out);

		if(k == 0)break;
	}

	e = clock();
	printf("##Encode process time:%fsec\n", (double)(e-s)/CLOCKS_PER_SEC);
	
	fclose(fd_get);
	fclose(fd_put);
	free(expanded_key);
}

void decode_circle(char* file_name_get, char* file_name_put)
{
	FILE* fd_get = fopen(file_name_get, "r");
	FILE* fd_put = fopen(file_name_put, "w");

	uint8_t *expanded_key; // expanded key
	expanded_key = aes_init(sizeof(key));
	aes_key_expansion(key, expanded_key);

	if(fd_get == NULL)
	{
		printf("Error file open!\n");
		exit(0);
	}

	clock_t s, e;
	s = clock();

	for(;;)
	{
		uint8_t code_in[16] = {'\n'};
		uint8_t code_out[16] = {'\n'};
		int k = decode_file_get(fd_get, code_in);
		if(k == -1)break;

		hex_array_print(code_in, "-Ciphered message:", 4);

		aes_inv_cipher(code_in, code_out, expanded_key);

		hex_array_print(code_out, "-Original message (after inv cipher):", 4);

		decode_file_printf(fd_put, code_out);

	}

	e = clock();
	printf("##Decode process time:%fsec\n", (double)(e-s)/CLOCKS_PER_SEC);
	
	fclose(fd_get);
	fclose(fd_put);
	free(expanded_key);
}