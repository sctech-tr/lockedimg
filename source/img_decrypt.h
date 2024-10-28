#ifndef IMG_DECRYPT_H
#define IMG_DECRYPT_H

#include <stdbool.h>

int decrypt_image(const char *file_path, const unsigned char *password, bool delete_after);

#endif
