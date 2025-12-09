#include <string.h>
#include "xor_cipher.h"

void xor_encrypt(char* data, const char* key) {
    if (data == NULL || key == NULL) return;
    size_t key_len = strlen(key);
    if (key_len == 0) return;
    
    size_t data_len = strlen(data);
    for (size_t i = 0; i < data_len; ++i) {
        data[i] ^= key[i % key_len];
    }
}
