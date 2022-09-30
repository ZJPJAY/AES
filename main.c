/*
 * @author Jackey
 */

#include <stdio.h>
#include "expanse.h"

int main() {

	/* AES加密 */
	printf("\nEncode--------------------------------------------------\n");
	encode_circle("simple.script", "encode.txt");

	/* AES解密 */
	printf("\nDecode--------------------------------------------------\n");
	decode_circle("encode.txt", "decode.txt");

	return 0;
}
