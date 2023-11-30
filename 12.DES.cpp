#include <stdio.h>
#include <stdint.h>
void generateKeys(uint64_t key, uint64_t* roundKeys);
void decrypt(uint64_t* data, uint64_t* roundKeys);
void permute(uint64_t* data, const int* permutation, int size);
void initialPermutation(uint64_t* data);
void finalPermutation(uint64_t* data);
void applyRound(uint64_t* data, uint64_t roundKey);
void fFunction(uint32_t* data, uint64_t roundKey);
int main() {
    uint64_t key, data;
    printf("Enter 64-bit key: ");
    scanf("%llx", &key);
    printf("Enter 64-bit data: ");
    scanf("%llx", &data);
    uint64_t roundKeys[16];
    generateKeys(key, roundKeys);
    initialPermutation(&data);
    decrypt(&data, roundKeys);
    finalPermutation(&data);
    printf("Decrypted data: %016llx\n", data);
    return 0;
}
void generateKeys(uint64_t key, uint64_t* roundKeys) {
    for (int i = 0; i < 16; ++i) {
        roundKeys[i] = key;
    }
}
void decrypt(uint64_t* data, uint64_t* roundKeys) {
}
void initialPermutation(uint64_t* data) {
}
void finalPermutation(uint64_t* data) {
}
void permute(uint64_t* data, const int* permutation, int size) {
}
void applyRound(uint64_t* data, uint64_t roundKey) {
    
}
void fFunction(uint32_t* data, uint64_t roundKey) {
}