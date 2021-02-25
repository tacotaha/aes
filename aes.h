#ifndef AES_H
#define AES_H

#include "tables.h"

void hexdump(uchar_t *, int r, int c);
static inline void dump_blk(uchar_t * b) {
  hexdump(b, 4, 4);
}

void byte_sub(uchar_t *);
void shift_rows(uchar_t *);
void mix_cols(uchar_t *);

void transpose(uchar_t *);
void crot(uchar_t * blk, int start, int end);

void encrypt(uchar_t * blk, uchar_t * key);
void decrypt(uchar_t * blk, uchar_t * key);

#endif                          /* AES_H */
