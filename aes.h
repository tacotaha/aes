#ifndef AES_H
#define AES_H

#include <inttypes.h>
#include "tables.h"

#define KEY_SIZE 128
#define BLK_SIZE (1 << 5)
#define NUM_WORDS (KEY_SIZE / BLK_SIZE)
#define NUM_ROUNDS (NUM_WORDS + 6)
#define KEY_EXP ((NUM_ROUNDS + 1) << 2)

void hexdump(uchar_t *, int r, int c);

static inline void dump_blk(uchar_t * b) {
  hexdump(b, 4, 4);
}

void byte_sub(uchar_t *);
void shift_rows(uchar_t *);
void mix_cols(uchar_t *);
void expand_key(uchar_t *, uint32_t *);

void transpose(uchar_t *);
void crot(uchar_t * blk, int start, int end);

void encrypt(uchar_t * blk, uchar_t * key);
void decrypt(uchar_t * blk, uchar_t * key);

#endif                          /* AES_H */
