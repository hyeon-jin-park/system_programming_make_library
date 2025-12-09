#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "xor_cipher.h"

int main() {
    char message[] = "Dynamic Linking Test!";
    const char* secret_key = "DynamicKey";

    printf("--- Shared Library Test ---\n");
    printf("Original Text      : %s\n", message);
    printf("\n");

    printf("--- Encrypting ---\n");
    xor_encrypt(message, secret_key);
    printf("Encrypted Text     : %s\n", message);
    printf("\n");

    printf("--- Decrypting ---\n");
    xor_decrypt(message, secret_key);
    printf("Decrypted Text     : %s\n", message);

    return 0;
}
