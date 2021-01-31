#include <stdlib.h>
#include <stdio.h>

void circular_rotate(char* msg, int start, int end){
    char tmp = msg[start];
    for(int i = start; i < end - 1; ++i)
        msg[i] = msg[i + 1];
    msg[end - 1] = tmp;
}

char* encrypt(char* msg, char* key){
    return NULL;
}

char* decrypt(char* msg, char* key){
    return NULL;
}
