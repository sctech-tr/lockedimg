#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include "img_decrypt.h"

#define BUFFER_SIZE 1024

int decrypt_image(const char *file_path, const unsigned char *password, bool delete_after) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Error opening encrypted file");
        return -1;
    }

    unsigned char iv[16] = {0};
    unsigned char key[32];
    memset(key, 0, sizeof(key));
    strncpy((char *)key, (const char *)password, sizeof(key) - 1);

    char decrypted_file[256];
    strncpy(decrypted_file, file_path, strlen(file_path) - strlen(".lockedimg"));
    decrypted_file[strlen(file_path) - strlen(".lockedimg")] = '\0';

    FILE *dec_file = fopen(decrypted_file, "wb");
    if (!dec_file) {
        perror("Error creating decrypted file");
        fclose(file);
        return -1;
    }

    unsigned char buffer[BUFFER_SIZE];
    unsigned char dec_buffer[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];
    int read_size, dec_size;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    while ((read_size = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        EVP_DecryptUpdate(ctx, dec_buffer, &dec_size, buffer, read_size);
        fwrite(dec_buffer, 1, dec_size, dec_file);
    }
    EVP_DecryptFinal_ex(ctx, dec_buffer, &dec_size);
    fwrite(dec_buffer, 1, dec_size, dec_file);

    EVP_CIPHER_CTX_free(ctx);
    fclose(file);
    fclose(dec_file);
    printf("File decrypted and saved as: %s\n", decrypted_file);

    if (delete_after) {
        remove(file_path);
        printf("Encrypted file deleted: %s\n", file_path);
    }
    return 0;
}
