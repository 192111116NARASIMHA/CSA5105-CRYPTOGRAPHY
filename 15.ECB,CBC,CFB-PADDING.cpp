#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

#define BLOCK_SIZE 16 // AES block size in bytes

void print_hex(const char *label, const unsigned char *data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; ++i) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void encrypt_ecb(const char *plaintext, unsigned char *ciphertext, const AES_KEY *key) {
    AES_encrypt((const unsigned char *)plaintext, ciphertext, key);
}

void decrypt_ecb(const unsigned char *ciphertext, char *plaintext, const AES_KEY *key) {
    AES_decrypt(ciphertext, (unsigned char *)plaintext, key);
}

void encrypt_cbc(const char *plaintext, unsigned char *ciphertext, const AES_KEY *key, const unsigned char *iv) {
    AES_cbc_encrypt((const unsigned char *)plaintext, ciphertext, BLOCK_SIZE, key, iv, AES_ENCRYPT);
}

void decrypt_cbc(const unsigned char *ciphertext, char *plaintext, const AES_KEY *key, const unsigned char *iv) {
    AES_cbc_encrypt(ciphertext, (unsigned char *)plaintext, BLOCK_SIZE, key, iv, AES_DECRYPT);
}

void encrypt_cfb(const char *plaintext, unsigned char *ciphertext, const AES_KEY *key, const unsigned char *iv) {
    AES_cfb_encrypt((const unsigned char *)plaintext, ciphertext, BLOCK_SIZE, key, iv, AES_ENCRYPT);
}

void decrypt_cfb(const unsigned char *ciphertext, char *plaintext, const AES_KEY *key, const unsigned char *iv) {
    AES_cfb_encrypt(ciphertext, (unsigned char *)plaintext, BLOCK_SIZE, key, iv, AES_DECRYPT);
}

int main() {
    const char key[] = "0123456789abcdef";
    const char iv[] = "1234567890123456";
    const char plaintext[] = "HELLO WORLD123456";
    unsigned char ciphertext[BLOCK_SIZE];
    char decrypted[BLOCK_SIZE + 1]; // +1 for null terminator

    AES_KEY aes_key;
    AES_set_encrypt_key((const unsigned char *)key, 128, &aes_key);

    // ECB Mode
    encrypt_ecb(plaintext, ciphertext, &aes_key);
    decrypt_ecb(ciphertext, decrypted, &aes_key);
    print_hex("ECB Ciphertext", ciphertext, BLOCK_SIZE);
    printf("ECB Decrypted: %s\n", decrypted);

    // CBC Mode
    encrypt_cbc(plaintext, ciphertext, &aes_key, (const unsigned char *)iv);
    decrypt_cbc(ciphertext, decrypted, &aes_key, (const unsigned char *)iv);
    print_hex("CBC Ciphertext", ciphertext, BLOCK_SIZE);
    printf("CBC Decrypted: %s\n", decrypted);

    // CFB Mode
    encrypt_cfb(plaintext, ciphertext, &aes_key, (const unsigned char *)iv);
    decrypt_cfb(ciphertext, decrypted, &aes_key, (const unsigned char *)iv);
    print_hex("CFB Ciphertext", ciphertext, BLOCK_SIZE);
    printf("CFB Decrypted: %s\n", decrypted);

    return 0;
}
