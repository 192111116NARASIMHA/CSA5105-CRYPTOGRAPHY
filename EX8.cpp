#include <stdio.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 0;
}

void breakAffineCipher(char ciphertext[], int length) {
    int freq[26] = {0};
    
    // Count the frequency of each letter in the ciphertext
    for (int i = 0; i < length; i++)
        freq[ciphertext[i] - 'A']++;

    // Find the most and second most frequent letters
    int maxIndex = 0, secondMaxIndex = 0;
    for (int i = 1; i < 26; i++) {
        if (freq[i] > freq[maxIndex]) {
            secondMaxIndex = maxIndex;
            maxIndex = i;
        } else if (freq[i] > freq[secondMaxIndex] && i != maxIndex) {
            secondMaxIndex = i;
        }
    }

    // Calculate a and b using the most and second most frequent letters
    int a = (maxIndex - secondMaxIndex + 26) % 26;
    int b = (ciphertext[0] - 'A' - a * ('E' - 'A') + 26) % 26;

    // Find the modular inverse of a
    int aInverse = modInverse(a, 26);

    // Decrypt the ciphertext
    printf("Decrypted Text: ");
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] != ' ')
            printf("%c", (aInverse * (ciphertext[i] - 'A' - b + 26) % 26) + 'A');
        else
            printf(" ");
    }
    printf("\n");
}

int main() {
    char ciphertext[] = "YOURCIPHERTEXT";  // Replace with your actual ciphertext
    int length = sizeof(ciphertext) - 1;   // Length of the ciphertext excluding the null terminator

    breakAffineCipher(ciphertext, length);

    return 0;
}
