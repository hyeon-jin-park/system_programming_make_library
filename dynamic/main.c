#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "xor_cipher.h"

void print_hex(const char* label, const char* data, size_t len) {
    printf("%-18s: ", label);
    for (size_t i = 0; i < len; ++i) {
        printf("%02X ", (unsigned char)data[i]);
    }
    printf("\n");
}

int main() {
    char message[] = "Dynamic Linking Test!";
    size_t message_len = strlen(message);
    const char* secret_key = "DynamicKey";

    printf("--- Shared Library Test ---\n");
    printf("Original Text      : %s\n", message);
    print_hex("Original (HEX)", message, message_len);
    printf("\n");

    printf("--- Encrypting ---\n");
    xor_encrypt(message, message_len, secret_key);
    print_hex("Encrypted (HEX)", message, message_len);
    printf("\n");

    printf("--- Decrypting ---\n");
    xor_decrypt(message, message_len, secret_key);
    printf("Decrypted Text     : %s\n", message);
    print_hex("Decrypted (HEX)", message, message_len);

    return 0;
}