#include <stdio.h>
#include <string.h>

#define SIZE 5

void prepareKey(char key[], char keyTable[SIZE][SIZE]);
void encrypt(char keyTable[SIZE][SIZE], char input[], char output[]);

int main() {
    char key[26], keyTable[SIZE][SIZE], input[100], output[100];

    printf("Enter the key: ");
    scanf("%s", key);

    prepareKey(key, keyTable);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ",keyTable[i][j]); 
        }
        printf("\n");
    }

    printf("Enter the plaintext (in uppercase): ");
    scanf("%s", input);

    encrypt(keyTable, input, output);

    printf("Encrypted text: %s\n", output);

    return 0;
}

void prepareKey(char key[], char keyTable[SIZE][SIZE]) {
    char temp[26];
    int k = 0;

    // Fill the key table with the key
    for (int i = 0; i < strlen(key); i++) {
        if (key[i] == 'J') {
            key[i] = 'I'; // Replace J with I
        }
        if (strchr(temp, key[i]) == NULL) {
            temp[k++] = key[i];
        }
    }

    // Fill the remaining cells of the key table with the alphabet (excluding key characters)
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') {
            continue;
        }
        if (strchr(temp, c) == NULL) {
            temp[k++] = c;
        }
    }

    // Fill the key table
    k = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            keyTable[i][j] = temp[k++];
        }
    }
}

void encrypt(char keyTable[SIZE][SIZE], char input[], char output[]) {
    int len = strlen(input);
    int i = 0;
    while (i < len) {
        char a = input[i++];
        char b = input[i++];
        int row1, col1, row2, col2;

        // Find the positions of characters in the key table
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                if (keyTable[j][k] == a) {
                    row1 = j;
                    col1 = k;
                }
                if (keyTable[j][k] == b) {
                    row2 = j;
                    col2 = k;
                }
            }
        }

        // Check if the letters are in the same row or column
        if (row1 == row2) {
            output[strlen(output)] = keyTable[row1][(col1 + 1) % SIZE];
            output[strlen(output)] = keyTable[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            output[strlen(output)] = keyTable[(row1 + 1) % SIZE][col1];
            output[strlen(output)] = keyTable[(row2 + 1) % SIZE][col2];
        } else {
            output[strlen(output)] = keyTable[row1][col2];
            output[strlen(output)] = keyTable[row2][col1];
        }
    }
}
