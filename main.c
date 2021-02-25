#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "aes.h"

int main(int argc, char **argv) {
  char *msg, *key;
  int mlen, num_blks;

  msg = "Hello World!!!!!";
  key = "password";

  mlen = strlen(msg);
  num_blks = ceil(mlen / 16.0);

  uchar_t *blk, *arr = malloc(sizeof(uchar_t) * mlen);
  memcpy(arr, msg, mlen);

  for (int i = 0; i < 16; ++i)
    arr[i] = i;

  printf("Message: %s\n", arr);
  printf("Message Len: %d\n", mlen);
  printf("Num Blocks: %d\n", num_blks);

  for (int i = 0; i < num_blks; ++i) {
    blk = arr + (i << 4);
    encrypt(blk, (uchar_t *) key);
  }

  free(arr);

  return 0;
}
