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

void sub_byte(uchar_t * blk) {
  unsigned short r, c;
  r = ((*blk & 0xf0) >> 4);
  c = *blk & 0xf;
  *blk = sbox[(r << 4) + c];
}

void byte_sub(uchar_t * blk) {
  for (int i = 0; i < 16; ++i)
    sub_byte(blk + i);
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

void g(uint32_t * v, int round) {
  uint8_t msb = (*v & (0xff << 24)) >> 24;
  *v <<= 8;
  *v |= msb;

  for (int i = 0; i < 4; ++i)
    sub_byte((uchar_t *) v + i);

  *v ^= rcon[round];
}

void expand_key(uchar_t * key, uint32_t * w) {
  uint32_t temp;

  for (int i = 0; i < NUM_WORDS; ++i)
    for (int j = 0; j < 4; ++j) {
      temp = key[4 * i + j];
      w[i] |= (temp << (8 * (3 - j)));
    }

  for (int i = NUM_WORDS; i < KEY_EXP; ++i) {
    temp = w[i - 1];
    if (i % NUM_WORDS == 0)
      g(&temp, i / NUM_WORDS - 1);
    else if (KEY_SIZE == 256 && i % 4 == 0)
      for (int j = 0; j < 4; ++j)
        sub_byte((uchar_t *) & temp + j);
    w[i] = w[i - NUM_WORDS] ^ temp;
  }
}

void encrypt(uchar_t * blk, uchar_t * key) {
  uint32_t *ek = malloc(KEY_EXP);
  if (!ek)
    return;

  expand_key(key, ek);

#if DEBUG
  printf("\nExpanded Key:\n");
  for (int i = 0; i < KEY_EXP; ++i)
    printf("0x%02x ", ek[i]);
  printf("\n");
#endif

  transpose(blk);

#if DEBUG
  printf("\nBlock: \n");
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

  free(ek);
}
