#ifndef _EXPANSE_H_
#define _EXPANSE_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void hex_array_print(uint8_t* out_print, char* dec, int out_pirint_len);

void init_file(char* file_name, uint8_t* str);

#endif