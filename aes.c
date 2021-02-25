#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "aes.h"

#define DEBUG 1

void hexdump(uchar_t * arr, int r, int c) {
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j)
      printf("0x%02x\t", arr[i * r + j]);
    printf("\n");
  }
}

void transpose(uchar_t * blk) {
  uchar_t t;
  for (int i = 0; i < 3; ++i)
    for (int j = i + 1; j < 4; ++j) {
      t = blk[(i << 2) + j];
      blk[(i << 2) + j] = blk[(j << 2) + i];
      blk[(j << 2) + i] = t;
    }
}

void crot(uchar_t * msg, int start, int end) {
  uchar_t tmp = msg[start];
  for (int i = start; i < end - 1; ++i)
    msg[i] = msg[i + 1];
  msg[end - 1] = tmp;
}

void byte_sub(uchar_t * blk) {
  unsigned short r, c;
  for (int i = 0; i < 16; ++i) {
    r = ((blk[i] & 0xf0) >> 4);
    c = blk[i] & 0xf;
    blk[i] = sbox[(r << 4) + c];
  }
}

void shift_rows(uchar_t * blk) {
  for (int i = 1; i < 4; ++i)
    for (int j = 0; j < i; ++j)
      crot(blk, i << 2, (i << 2) + 4);
}

void mix_cols(uchar_t * blk) {
  uchar_t res[16] = { 0 };
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      for (int k = 0; k < 4; ++k)
        switch (m0[i * 4 + k]) {
          case 0x01:
            res[i * 4 + j] ^= blk[k * 4 + j];
            break;
          case 0x02:
            res[i * 4 + j] ^= m2[blk[k * 4 + j]];
            break;
          case 0x03:
            res[i * 4 + j] ^= m3[blk[k * 4 + j]];
            break;
        };
  memcpy(blk, res, sizeof(uchar_t) << 4);
}

void encrypt(uchar_t * blk, uchar_t * key) {
  transpose(blk);

#if DEBUG
  printf("Block: \n");
  dump_blk(blk);
#endif

  byte_sub(blk);

#if DEBUG
  printf("\nByte sub: \n");
  dump_blk(blk);
#endif

  shift_rows(blk);

#if DEBUG
  printf("\nShift Rows: \n");
  dump_blk(blk);
#endif

  mix_cols(blk);

#if DEBUG
  printf("\nMix Cols: \n");
  dump_blk(blk);
#endif
}
