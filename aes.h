#ifndef AES_H
#define AES_H

#define BLK_SIZE 128
#define KEY_ROUNDS 10
#define BSIZE 16 << 4

typedef unsigned char uchar_t;

extern uchar_t minv[BSIZE];
extern uchar_t sbox[BSIZE];

void hexdump(uchar_t *, int r, int c);
void dump_block(uchar_t *);

void gen_subkeys(uchar_t * key, uchar_t ** subkeys);
void bsub(uchar_t * msg, int mlen);

void circular_rotate(uchar_t * msg, int start, int end);

uchar_t *encrypt(uchar_t * msg, uchar_t * key);
uchar_t *decrypt(uchar_t * msg, uchar_t * key);

#endif                          /* AES_H */
