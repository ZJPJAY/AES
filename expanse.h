#ifndef _EXPANSE_H_
#define _EXPANSE_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void hex_array_print(uint8_t* out_print, char* dec, int out_pirint_len);

void init_file(char* file_name, uint8_t* str);

/* 
    名称：AES加密函数
    参数：file_name_get      需要被加密的文件
         file_name_put      存放加密后的文件
    功能：将文件进行AES加密，可在函数中选择AES128、AES196和AES256三种等级加密
*/
void encode_circle(char* file_name_get, char* file_name_put);

/* 
    名称：AES解密函数
    参数：file_name_get      已经被加密的文件
         file_name_put      存放解密后的文件
    功能：将文件进行AES解密，可在函数中选择AES128、AES196和AES256三种等级解密
*/
void decode_circle(char* file_name_get, char* file_name_put);

#endif