#ifndef HEADER_H
#define HEADER_H

#define MAX_PASSWORD_LENGTH 50
#define VAULT_FOLDER "password_vault/"
#define VAULT_FILE "vault.txt"
#define PASSKEY "yourpasskey"

void displayMenu();
void addPassword();
void generatePassword();
void encryptPassword(char *password);
void decryptPassword(char *encryptedPassword);
void savePasswordToFile(char *serviceName, char *username, char *password);
void loadPasswordFromFile();
int authenticate();

#endif /* HEADER_H */
