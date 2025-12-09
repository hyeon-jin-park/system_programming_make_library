#ifndef XOR_CIPHER_H
#define XOR_CIPHER_H

#include <stdlib.h> // size_t 타입을 사용하기 위해 포함합니다.

void xor_encrypt(char* data, size_t data_len, const char* key);

void xor_decrypt(char* data, size_t data_len, const char* key);

#endif // XOR_CIPHER_H