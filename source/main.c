#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "img_encrypt.h"
#include "img_decrypt.h"
#include "prompt_utils.h"

// List of supported image file extensions
// also added .lockedimg for double or triple locking :troll:
const char *supported_extensions[] = {".jpg", ".jpeg", ".png", ".bmp", ".gif", ".ico", ".bruh", ".jfif", ".svg", ".lockedimg"}; // no cheating lol

bool is_image_file(const char *file_path) {
    for (int i = 0; supported_extensions[i]; i++) {
        if (strlen(file_path) >= strlen(supported_extensions[i]) &&
            strcasecmp(file_path + strlen(file_path) - strlen(supported_extensions[i]), supported_extensions[i]) == 0) {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    char action[10] = "";
    char file_path[256] = "";
    char password[256] = "";
    bool delete_after = true;

    if (argc > 1) {
        if (strcmp(argv[1], "encrypt") == 0 || strcmp(argv[1], "decrypt") == 0) {
            strncpy(action, argv[1], sizeof(action) - 1);
            if (argc >= 3) {
                strncpy(file_path, argv[2], sizeof(file_path) - 1);
                if (!is_image_file(file_path)) {
                    printf("Error: %s is not a supported image file.\n", file_path);
                    return 1;
                }
                if (argc >= 4) {
                    strncpy(password, argv[3], sizeof(password) - 1);
                    if (argc == 5 && strcmp(argv[4], "--no-deletion") == 0) {
                        delete_after = false;
                    }
                }
            }
        } else if (strcmp(argv[1], "--help") == 0) {
            printf("Locked Image Tool (lockedimg) v1.0\n");
            printf("Usage: %s <action> <image file path> <password> [--no-deletion]\n", argv[0]);
            printf("Actions available: encrypt, decrypt\n");
            printf("Optional parameters:\n");
            printf("  --no-deletion: Do not delete the encrypted file after decryption\n");
            printf("  --help: Display this help message\n");
            return 0;
        } else {
            printf("Invalid action. Use 'encrypt' or 'decrypt'.\n");
            return 1;
        }
    } else {
        prompt_for_input(action, "Enter action (encrypt or decrypt)");
        prompt_for_input(file_path, "Enter image file path (with .lockedimg if you're decrypting)");
        if (!is_image_file(file_path)) {
            printf("Error: %s is not a supported image file.\n", file_path);
            return 1;
        }
        prompt_for_input(password, "Enter password");

        if (strcasecmp(action, "decrypt") == 0) {
            char delete_choice[10];
            prompt_for_input(delete_choice, "Delete encrypted file after decryption? (yes or no)");
            if (strcasecmp(delete_choice, "no") == 0) {
                delete_after = false;
            }
        }
    }

    if (strcmp(action, "encrypt") == 0) {
        if (encrypt_image(file_path, (const unsigned char *)password) != 0) {
            return 1;
        }
    } else if (strcmp(action, "decrypt") == 0) {
        if (decrypt_image(file_path, (const unsigned char *)password, delete_after) != 0) {
            return 1;
        }
    } else {
        printf("Invalid action. Use 'encrypt' or 'decrypt'.\n");
        return 1;
    }

    return 0;
}