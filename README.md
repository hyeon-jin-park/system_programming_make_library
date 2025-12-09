# C 라이브러리 빌드 및 링킹 프로젝트

이 프로젝트는 C언어에서 라이브러리를 생성하고 사용하는 세 가지 주요 방법을 시연합니다.

1.  **정적 라이브러리 (Static Library)**
2.  **공유 라이브러리 (Shared Library / Dynamic Linking)**
3.  **런타임 로딩 (Runtime Loading / Dynamic Loading)**

각각의 방법은 간단한 XOR 암호화/복호화 라이브러리를 예제로 사용하여 설명됩니다.

## 프로젝트 구조

프로젝트는 세 개의 독립적인 디렉토리로 구성되어 있으며, 각 디렉토리는 특정 링킹 방식을 보여줍니다.

-   `static/`: 정적 라이브러리(`.a`)를 생성하고, 이를 실행 파일에 링크하는 과정을 보여줍니다.
-   `dynamic/`: 공유 라이브러리(`.so`)를 생성하고, 컴파일 시점에 링크하는 과정을 보여줍니다.
-   `runtime/`: 프로그램 실행 중에 공유 라이브러리(`.so`)를 명시적으로 로드하고 사용하는 과정을 보여줍니다.

## 라이브러리 기능: XOR 암호화

이 프로젝트에서 사용되는 `libxor` 라이브러리는 두 가지 함수를 제공합니다.

-   `void xor_encrypt(char* data, size_t data_len, const char* key)`: 데이터를 제자리에서 암호화합니다.
-   `void xor_decrypt(char* data, size_t data_len, const char* key)`: 데이터를 제자리에서 복호화합니다.

XOR 연산의 특성상, 암호화와 복호화의 로직은 동일합니다.

---

## 빌드 및 실행 방법

각 디렉토리로 이동하여 아래의 명령어를 순서대로 실행하세요.

### 1. 정적 라이브러리 (Static)

라이브러리 코드가 실행 파일에 완전히 포함되는 방식입니다.

```bash
# 1. static 디렉토리로 이동
cd static

# 2. 라이브러리 소스를 오브젝트 파일(.o)로 컴파일
gcc -c encrypt.c decrypt.c

# 3. 오브젝트 파일들을 묶어 정적 라이브러리(libxor.a) 생성
ar rcs libxor.a encrypt.o decrypt.o

# 4. 메인 프로그램과 라이브러리를 링크하여 실행 파일(main_static) 생성
gcc main.c -L. -lxor -o main_static

# 5. 실행
./main_static
```

### 2. 공유 라이브러리 (Dynamic)

실행 시점에 운영체제가 라이브러리를 메모리에 로드하여 여러 프로그램이 공유하는 방식입니다.

```bash
# 1. dynamic 디렉토리로 이동
cd dynamic

# 2. 위치 독립 코드(-fPIC) 옵션으로 오브젝트 파일 컴파일
gcc -fPIC -c encrypt.c decrypt.c

# 3. 오브젝트 파일들을 묶어 공유 라이브러리(libxor.so) 생성
gcc -shared -o libxor.so encrypt.o decrypt.o

# 4. 메인 프로그램과 라이브러리를 링크하여 실행 파일(main_dynamic) 생성
gcc main.c -L. -lxor -o main_dynamic

# 5. 실행 (LD_LIBRARY_PATH 환경 변수 설정 필요)
export LD_LIBRARY_PATH=.
./main_dynamic
```

### 3. 런타임 로딩 (Runtime)

프로그램이 실행 중에 `dlopen()` 함수를 사용하여 라이브러리를 직접 로드하는 방식입니다.

```bash
# 1. runtime 디렉토리로 이동
cd runtime

# 2. 공유 라이브러리(libxor.so) 생성 (dynamic과 동일)
gcc -fPIC -c encrypt.c decrypt.c
gcc -shared -o libxor.so encrypt.o decrypt.o

# 3. 메인 프로그램을 컴파일 (-ldl 옵션 필요)
gcc main_runtime.c -ldl -o main_runtime

# 4. 실행 (LD_LIBRARY_PATH 환경 변수 설정 필요)
export LD_LIBRARY_PATH=.
./main_runtime
```