#include <stdio.h>
#include "header.h"

int main() {
    if (!authenticate()) {
        printf("Incorrect passkey. Exiting...\n");
        return 1;
    }

    char choice;
    do {
        displayMenu();
        scanf(" %c", &choice);
        switch (choice) {
            case '1':
                addPassword();
                break;
            case '2':
                generatePassword();
                break;
            case '3':
                loadPasswordFromFile();
                break;
            case '4':
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != '4');

    return 0;
}
