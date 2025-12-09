#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h> // 동적 로딩(dlopen, dlsym, dlclose) 함수들을 위해 포함합니다.


int main() {
    void *handle;
    void (*encrypt_func)(char*, const char*);
    void (*decrypt_func)(char*, const char*);
    char *error;

    char message[] = "Runtime Loading Test!";
    const char* secret_key = "KeyRuntime";

    printf("--- Runtime Loading Test ---\n");
    printf("Original Text      : %s\n", message);
    printf("\n");

    handle = dlopen("./libxor.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    encrypt_func = dlsym(handle, "xor_encrypt");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    decrypt_func = dlsym(handle, "xor_decrypt");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    printf("--- Encrypting ---\n");
    encrypt_func(message, secret_key);
    printf("Encrypted Text     : %s\n", message);
    printf("\n");

    printf("--- Decrypting ---\n");
    decrypt_func(message, secret_key);
    printf("Decrypted Text     : %s\n", message);

    if (dlclose(handle) < 0) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    return 0;
}