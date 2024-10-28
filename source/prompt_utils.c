#include <stdio.h>
#include <string.h>
#include "prompt_utils.h"

void prompt_for_input(char *input, const char *prompt_text) {
    printf("%s: ", prompt_text);
    fgets(input, 256, stdin);
    input[strcspn(input, "\n")] = 0;
}
