#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "header.h"

void displayMenu() {
    printf("\nPassword Manager Menu\n");
    printf("1. Add a password\n");
    printf("2. Generate a random password\n");
    printf("3. Show saved passwords\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

void addPassword() {
    char serviceName[50];
    char username[50];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter service name: ");
    scanf("%s", serviceName);
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    encryptPassword(password);
    savePasswordToFile(serviceName, username, password);
    printf("Password saved successfully.\n");
}

void generatePassword() {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?";
    const int charsetLength = strlen(charset);
    char generatedPassword[MAX_PASSWORD_LENGTH + 1];

    srand(time(NULL));

    printf("Generated password: ");
    for (int i = 0; i < MAX_PASSWORD_LENGTH; i++) {
        generatedPassword[i] = charset[rand() % charsetLength];
    }
    generatedPassword[MAX_PASSWORD_LENGTH] = '\0';
    printf("%s\n", generatedPassword);
}

void encryptPassword(char *password) {
    for (int i = 0; i < strlen(password); i++) {
        password[i] = password[i] ^ 0xFF;
    }
}

void decryptPassword(char *encryptedPassword) {
    for (int i = 0; i < strlen(encryptedPassword); i++) {
        encryptedPassword[i] = encryptedPassword[i] ^ 0xFF;
    }
}

void savePasswordToFile(char *serviceName, char *username, char *password) {
    char filePath[100]; // Adjust the size according to your needs
    sprintf(filePath, "%s%s", VAULT_FOLDER, VAULT_FILE);
    FILE *file = fopen(filePath, "a");
    if (file != NULL) {
        fprintf(file, "%s %s %s\n", serviceName, username, password);
        fclose(file);
    } else {
        printf("Error saving password.\n");
    }
}

void loadPasswordFromFile() {
    char filePath[100]; // Adjust the size according to your needs
    sprintf(filePath, "%s%s", VAULT_FOLDER, VAULT_FILE);
    FILE *file = fopen(filePath, "r");
    if (file != NULL) {
        char serviceName[50];
        char username[50];
        char encryptedPassword[MAX_PASSWORD_LENGTH];
        while (fscanf(file, "%s %s %s", serviceName, username, encryptedPassword) != EOF) {
            decryptPassword(encryptedPassword);
            printf("Service: %s, Username: %s, Password: %s\n", serviceName, username, encryptedPassword);
        }
        fclose(file);
    } else {
        printf("No passwords saved yet.\n");
    }
}

int authenticate() {
    char passkey[50];
    printf("Enter passkey to access the password manager: ");
    scanf("%s", passkey);
    return strcmp(passkey, PASSKEY) == 0;
}
