#include <stdio.h>
#define BLOCK_SIZE_64 8
#define BLOCK_SIZE_128 16
void left_shift(unsigned char *data, int size) {
    unsigned char carry = 0;
    for (int i = 0; i < size; i++) {
        unsigned char next_carry = data[i] >> 7;
        data[i] = (data[i] << 1) | carry; 
        carry = next_carry; 
    }
}
void xor_arrays(unsigned char *dest, unsigned char *src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] ^= src[i];
    }
}
int main() {
    unsigned char zero_block_64[BLOCK_SIZE_64] = {0};
    unsigned char zero_block_128[BLOCK_SIZE_128] = {0};
    unsigned char const_64[BLOCK_SIZE_64] = {0x1B, 0x36, 0x6C, 0x9A, 0xD2, 0xE5, 0xC8, 0x18};
    unsigned char const_128[BLOCK_SIZE_128] = {0x87, 0xC2, 0x9E, 0xD5, 0x78, 0x3F, 0x9A, 0xCA,
                                                0x8F, 0x37, 0x1A, 0x5A, 0xE5, 0x4D, 0xD0, 0x50};
    unsigned char subkey_64[BLOCK_SIZE_64];
    for (int i = 0; i < BLOCK_SIZE_64; i++) {
        subkey_64[i] = zero_block_64[i];
    }
    left_shift(subkey_64, BLOCK_SIZE_64);
        if (zero_block_64[0] & 0x80) {
        xor_arrays(subkey_64, const_64, BLOCK_SIZE_64);
    }
        unsigned char subkey_2_64[BLOCK_SIZE_64];
        for (int i = 0; i < BLOCK_SIZE_64; i++) {
        subkey_2_64[i] = subkey_64[i];
    }
        left_shift(subkey_2_64, BLOCK_SIZE_64);
        if (subkey_64[0] & 0x80) {
        xor_arrays(subkey_2_64, const_64, BLOCK_SIZE_64);
    }
    unsigned char subkey_128[BLOCK_SIZE_128];
    for (int i = 0; i < BLOCK_SIZE_128; i++) {
        subkey_128[i] = zero_block_128[i];
    }
    left_shift(subkey_128, BLOCK_SIZE_128);
    if (zero_block_128[0] & 0x80) {
        xor_arrays(subkey_128, const_128, BLOCK_SIZE_128);
    }
    unsigned char subkey_2_128[BLOCK_SIZE_128];
    for (int i = 0; i < BLOCK_SIZE_128; i++) {
        subkey_2_128[i] = subkey_128[i];
    }
    left_shift(subkey_2_128, BLOCK_SIZE_128);
    if (subkey_128[0] & 0x80) {
        xor_arrays(subkey_2_128, const_128, BLOCK_SIZE_128);
    }
    printf("Subkey 1 (64-bit): ");
    for (int i = 0; i < BLOCK_SIZE_64; i++) {
        printf("%02X ", subkey_64[i]);
    }
    printf("\n");
    printf("Subkey 2 (64-bit): ");
    for (int i = 0; i < BLOCK_SIZE_64; i++) {
        printf("%02X ", subkey_2_64[i]);
    }
    printf("\n");
    printf("Subkey 1 (128-bit): ");
    for (int i = 0; i < BLOCK_SIZE_128; i++) {
        printf("%02X ", subkey_128[i]);
    }
    printf("\n");
    printf("Subkey 2 (128-bit): ");
    for (int i = 0; i < BLOCK_SIZE_128; i++) {
        printf("%02X ", subkey_2_128[i]);
    }
    printf("\n");
    return 0;
}