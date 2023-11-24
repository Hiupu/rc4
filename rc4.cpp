#include <stdio.h>
#include <stdlib.h>
#include <cstring>

void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

void rc4_init(unsigned char *key, int key_length, unsigned char S[256]) {
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_length]) % 256;
        swap(&S[i], &S[j]);
    }
}

void rc4_crypt(unsigned char *input, unsigned char *output, int length, unsigned char S[256]) {
    int i = 0, j = 0;
    for (int k = 0; k < length; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(&S[i], &S[j]);

        int t = (S[i] + S[j]) % 256;
        output[k] = input[k] ^ S[t];
    }
}

int main() {
    // Nhập key từ bàn phím
    printf("Enter key: ");
    char key[256];
    scanf("%s", key);
    int key_length = strlen(key);

    // Nhập plaintext từ bàn phím
    printf("Enter plaintext: ");
    char plaintext[256];
    scanf(" %[^\n]", plaintext);
    int plaintext_length = strlen(plaintext);

    // Chuyển đổi key và plaintext từ char* sang unsigned char*
    unsigned char u_key[256];
    memcpy(u_key, key, key_length);

    unsigned char u_plaintext[256];
    memcpy(u_plaintext, plaintext, plaintext_length);

    // Khởi tạo S-box
    unsigned char S[256];
    rc4_init(u_key, key_length, S);

    // Mã hóa dữ liệu
    unsigned char ciphertext[plaintext_length];
    rc4_crypt(u_plaintext, ciphertext, plaintext_length, S);

    // Hiển thị kết quả
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < plaintext_length; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}