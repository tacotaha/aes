#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "aes.h"

int main(int argc, char **argv) {
  char *msg;
  int mlen, num_blks;
  uchar_t key[4 * NUM_WORDS] =
    { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88,
0x09, 0xcf, 0x4f, 0x3c };

  msg = "Hello World!!!!!";
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
    encrypt(blk, key);
  }

  free(arr);

  return 0;
}
