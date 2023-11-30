#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_CHAR 26

void decryptAffine(char *text, int key[]) {
    int length = strlen(text);

    for (int i = 0; i < length; i++) {
        if (isupper(text[i])) {
            text[i] = ((key[0] * (text[i] - 'A')) % 26 + key[1]) % 26 + 'A';
        } else if (islower(text[i])) {
            text[i] = ((key[0] * (text[i] - 'a')) % 26 + key[1]) % 26 + 'a';
        }
    }
}

int findMostFreqLetter(char *text) {
    int count[MAX_CHAR] = {0};
    int max = 0;
    char mostFreqLetter = 'A';

    for (int i = 0; i < strlen(text); i++) {
        if (isupper(text[i])) {
            count[text[i] - 'A']++;
        } else if (islower(text[i])) {
            count[text[i] - 'a']++;
        }
    }

    for (int i = 0; i < MAX_CHAR; i++) {
        if (count[i] > max) {
            max = count[i];
            mostFreqLetter = i + 'A';
        }
    }

    return mostFreqLetter;
}

int main() {
    char *text = "UURZHBGF HHUB D FTK NM HF UZX B NHQR QDJ Q UU RXD Y B";
    printf("Original Cipher Text: %s\n", text);

    char mostFreqLetter = findMostFreqLetter(text);
    printf("Most Frequently Occurring Letter: %c\n", mostFreqLetter);

    for (int i = 0; i < MAX_CHAR; i++) {
        for (int j = 0; j < MAX_CHAR; j++) {
            if (i != 0 && j != 0) {
                int key[] = {i, j};
                decryptAffine(text, key);
                char mostFreqLetterNew = findMostFreqLetter(text);

                printf("Key: (%d, %d), Decrypted Text: %s\n", i, j, text);

                if (mostFreqLetterNew == 'U') {
                    printf("Affine Cipher Decryption Successful!\n");
                    printf("Decrypted Text: %s\n", text);
                    return 0;
                }
            }
        }
    }

    printf("Failed to decrypt the ciphertext.\n");
    return 0;
}


