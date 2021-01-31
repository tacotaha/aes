#include <stdio.h>
#include <stdlib.h>

#include "aes.h"

int main(int argc, char **argv) {
    char *msg, *key, *result;

    msg = "Hello World";
    key = "password";

    printf("msg: %s\n", msg);
    printf("key: %s\n", key);

    result = encrypt(msg, key);

    return 0;
}
