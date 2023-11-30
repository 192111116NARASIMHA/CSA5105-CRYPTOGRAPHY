#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform CBC-MAC on a one-block message X
void cbc_mac(unsigned char K[], unsigned char X[], unsigned char T[]) {
    // Assume block size is 16 bytes (128 bits)
    int block_size = 16;

    // Perform CBC encryption on the one-block message X
    for (int i = 0; i < block_size; i++) {
        X[i] ^= T[i];  // XOR the message with the previous MAC value
    }

    // Copy the encrypted message into the MAC result (T)
    for (int i = 0; i < block_size; i++) {
        T[i] = X[i];
    }
}

int main() {
    // Key K for CBC-MAC
    unsigned char K[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};

    // One-block message X
    unsigned char X[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};

    // Calculate the CBC-MAC of the one-block message X
    unsigned char T[16];
    memcpy(T, K, 16); // Initialize the CBC-MAC with the key
    cbc_mac(K, X, T);

    // Print the CBC-MAC for the one-block message X
    printf("MAC(K, X): ");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", T[i]);
    }
    printf("\n");

    // Calculate the CBC-MAC for the two-block message X || (X ? T)
    unsigned char X_concat[32];
    memcpy(X_concat, X, 16); // Copy X into the first block of the concatenated message
    for (int i = 0; i < 16; i++) {
        X_concat[16 + i] = X[i] ^ T[i]; // X ? T
    }

    // Calculate the CBC-MAC of the two-block message X || (X ? T)
    unsigned char T_concat[16];
    memcpy(T_concat, K, 16); // Initialize the CBC-MAC with the key
    cbc_mac(K, X_concat, T_concat);

    // Print the CBC-MAC for the two-block message X || (X ? T)
    printf("MAC(K, X || (X ? T)): ");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", T_concat[i]);
    }
    printf("\n");

    return 0;
}