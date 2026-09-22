#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

void xorEncrypt(char *message, char *key) {
    int keyLen = strlen(key);
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] ^= key[i % keyLen];
    }
}

void encryptFile(const char *filename, const char *message, const char *key) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    xorEncrypt((char *)message, key);
    fprintf(file, "%s", message);

    fclose(file);
}

void decryptFile(const char *filename, const char *key) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);

    xorEncrypt(buffer, key);

    printf("%s\n", buffer);
    free(buffer);
}

int main() {
    char choice[20];
    printf("Enter 'encrypt' or 'decrypt': ");
    if (fgets(choice, sizeof(choice), stdin) == NULL) {
        printf("Invalid choice.\n");
        return 1;
    }
    choice[strcspn(choice, "\n")] = '\0';

    if (strncmp(choice, "encrypt", sizeof("encrypt")) == 0) {
        char filename[50], message[256], key[256];
        printf("Enter the filename: ");
        if (fgets(filename, sizeof(filename), stdin) == NULL || filename[0] == '\n') {
            printf("Invalid choice.\n");
            return 1;
        }
        filename[strcspn(filename, "\n")] = '\0';
        printf("Enter the message to encrypt: ");
        if (fgets(message, sizeof(message), stdin) == NULL || message[0] == '\n') {
            printf("Invalid choice.\n");
            return 1;
        }
        message[strcspn(message, "\n")] = '\0';
        printf("Enter the encryption key: ");
        if (fgets(key, sizeof(key), stdin) == NULL || key[0] == '\n') {
            printf("Invalid choice.\n");
            return 1;
        }
        key[strcspn(key, "\n")] = '\0';
        encryptFile(filename, message, key);
    } else if (strncmp(choice, "decrypt", sizeof(choice)) == 0) {
        char key[256], filename[50];
        printf("Enter the filename: ");
        if (fgets(filename, sizeof(filename), stdin) == NULL || filename[0] == '\n') {
            printf("Invalid choice.\n");
            return 1;
        }
        filename[strcspn(filename, "\n")] = '\0';
        printf("Enter the decryption key: ");
        if (fgets(key, sizeof(key), stdin) == NULL || key[0] == '\n') {
            printf("Invalid choice.\n");
            return 1;
        }
        key[strcspn(key, "\n")] = '\0';
        decryptFile(filename, key);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
