#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

void encryptDES3_CBC(const char *input, const char *key, const char *iv, char *output) {
    DES_cblock key1, key2, key3, ivec;
    DES_key_schedule ks1, ks2, ks3;

    // Set the keys
    memcpy(key1, key, 8);
    memcpy(key2, key + 8, 8);
    memcpy(key3, key + 16, 8);

    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    // Set the IV
    memcpy(ivec, iv, 8);

    // Encrypt the data in CBC mode
    DES_ede3_cbc_encrypt((unsigned char *)input, (unsigned char *)output, strlen(input), &ks1, &ks2, &ks3, &ivec, DES_ENCRYPT);
}

int main() {
    const char *plaintext = "Hello, CBC mode!";
    const char *key = "0123456789abcdef0123456789abcdef0123456789abcdef";
    const char *iv = "12345678";

    char ciphertext[1024];
    
    encryptDES3_CBC(plaintext, key, iv, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
