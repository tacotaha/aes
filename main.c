#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aes.h"

int main(int argc, char **argv) {
  const char *msg = "Hello World!";
  //const char *key = "password";
  const int mlen = strlen(msg);

  uchar_t *tmp = malloc(sizeof(uchar_t) * mlen);

  memcpy(tmp, msg, mlen);

  printf("%s\n", tmp);

  hexdump(tmp, 1, mlen);
  bsub(tmp, mlen);
  hexdump(tmp, 1, mlen);

  free(tmp);
  return 0;
}
