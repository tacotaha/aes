#ifndef AES_H
#define AES_H

#define BLK_SIZE 128
#define KEY_ROUNDS 10

void dump_block(char*);
void gen_subkeys(char* key, char** subkeys);

char* encrypt(char* msg, char* key);
char* decrypt(char* msg, char* key);

#endif                          /* AES_H */
