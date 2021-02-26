#ifndef TABLES_H
#define TABLES_H

#include <inttypes.h>

#define BSIZE (16 << 4)

typedef unsigned char uchar_t;

extern uchar_t minv[BSIZE];
extern uchar_t sbox[BSIZE];
extern uint32_t rcon[10];
extern uchar_t m0[16];
extern uchar_t m2[256];
extern uchar_t m3[256];
extern uchar_t m9[256];

#endif                          /* TABLES_H */
