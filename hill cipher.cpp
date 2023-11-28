#include <stdio.h>
#include <string.h>
int charToNum(char ch) {
    return (ch >= 'a' && ch <= 'z') ? ch - 'a' : (ch >= 'A' && ch <= 'Z') ? ch - 'A' : -1;
}
char numToChar(int num) {
    return (char) (num + 'A');
}
void hillCipherEncrypt(char *message, int key[2][2]) {
    int len = strlen(message);
    int i, j;

    for (i = 0; i < len; i += 2) {
        int block[2] = {charToNum(message[i]), (i + 1 < len) ? charToNum(message[i + 1]) : 0};
        int result[2] = {0};
        for (j = 0; j < 2; j++) {
            result[j] = (key[j][0] * block[0] + key[j][1] * block[1]) % 26;
            result[j] = (result[j] + 26) % 26; 
        }
        for (j = 0; j < 2; j++) {
            printf("%c", numToChar(result[j]));
        }
    }
    printf("\n");
}

int main() {
    char message[100];
    int key[2][2];
   
    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; 
    printf("\nOriginal Message: %s\n", message);
     printf("enyer the key:");
    for(int i=0;i<2;i++)
    	for(int j=0;j<2;j++)
    		scanf("%d",&key[i][j]);
    printf("Key Matrix:\n| %d %d |\n| %d %d |\n", key[0][0], key[0][1], key[1][0], key[1][1]);
    printf("\nEncrypted Message: ");
    hillCipherEncrypt(message, key);

    return 0;
}