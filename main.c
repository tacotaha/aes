#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aes.h"

int main(int argc, char **argv) {
    const char* msg = "Hello World!";
    const char* key = "password";
    char *tmp = malloc(sizeof(char) * strlen(msg));

    memcpy(tmp, msg, strlen(msg));

    printf("msg: %s\n", msg);
    printf("key: %s\n", key);

    circular_rotate(tmp, 0, strlen(tmp));
    circular_rotate(tmp, 0, strlen(tmp));

    printf("%s\n", tmp);
    free(tmp);

    //r1 = encrypt(msg, key);
    //r2 = decrypt(r1, key);

    return 0;
}
