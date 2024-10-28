#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include "img_encrypt.h"

#define BUFFER_SIZE 1024

int encrypt_image(const char *file_path, const unsigned char *password) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    unsigned char iv[16] = {0};
    unsigned char key[32];
    memset(key, 0, sizeof(key));
    strncpy((char *)key, (const char *)password, sizeof(key) - 1);

    char encrypted_file[256];
    snprintf(encrypted_file, sizeof(encrypted_file), "%s.lockedimg", file_path);
    FILE *enc_file = fopen(encrypted_file, "wb");
    if (!enc_file) {
        perror("Error creating encrypted file");
        fclose(file);
        return -1;
    }

    unsigned char buffer[BUFFER_SIZE];
    unsigned char enc_buffer[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];
    int read_size, enc_size;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    while ((read_size = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        EVP_EncryptUpdate(ctx, enc_buffer, &enc_size, buffer, read_size);
        fwrite(enc_buffer, 1, enc_size, enc_file);
    }
    EVP_EncryptFinal_ex(ctx, enc_buffer, &enc_size);
    fwrite(enc_buffer, 1, enc_size, enc_file);

    EVP_CIPHER_CTX_free(ctx);
    fclose(file);
    fclose(enc_file);
    printf("File encrypted and saved as: %s\n", encrypted_file);
    return 0;
}
