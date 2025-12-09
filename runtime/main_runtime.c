#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h> // 동적 로딩(dlopen, dlsym, dlclose) 함수들을 위해 포함합니다.

// 라이브러리에서 가져올 함수의 원형과 일치하는 함수 포인터 타입을 정의합니다.
typedef void (*xor_func_t)(char*, size_t, const char*);

void print_hex(const char* label, const char* data, size_t len) {
    printf("%-18s: ", label);
    for (size_t i = 0; i < len; ++i) {
        printf("%02X ", (unsigned char)data[i]);
    }
    printf("\n");
}

int main() {
    char message[] = "Runtime Loading Test!";
    size_t message_len = strlen(message);
    const char* secret_key = "RuntimeKey";

    printf("--- Runtime Loading Test ---\n");
    printf("Original Text      : %s\n", message);
    print_hex("Original (HEX)", message, message_len);
    printf("\n");

    // 1. 공유 라이브러리 파일을 엽니다.
    void* handle = dlopen("./libxor.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "라이브러리 로딩 오류: %s\n", dlerror());
        return 1;
    }

    // dlerror()를 호출하여 이전 에러 상태를 초기화합니다.
    dlerror();

    // 2. 라이브러리에서 함수들의 주소를 찾습니다.
    xor_func_t encrypt_func = (xor_func_t)dlsym(handle, "xor_encrypt");
    const char* error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "함수 'xor_encrypt' 찾기 오류: %s\n", error);
        dlclose(handle);
        return 1;
    }

    xor_func_t decrypt_func = (xor_func_t)dlsym(handle, "xor_decrypt");
    error = dlerror();
    if (error != NULL) {
        fprintf(stderr, "함수 'xor_decrypt' 찾기 오류: %s\n", error);
        dlclose(handle);
        return 1;
    }

    // 3. 함수 포인터를 통해 라이브러리 함수를 사용합니다.
    printf("--- Encrypting ---\n");
    encrypt_func(message, message_len, secret_key);
    print_hex("Encrypted (HEX)", message, message_len);
    printf("\n");

    printf("--- Decrypting ---\n");
    decrypt_func(message, message_len, secret_key);
    printf("Decrypted Text     : %s\n", message);
    print_hex("Decrypted (HEX)", message, message_len);

    // 4. 사용이 끝난 라이브러리를 닫습니다.
    dlclose(handle);

    return 0;
}