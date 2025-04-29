#include<stddef.h>

#include "strstack.h"

char * M = 0;
size_t M_size = 0;
char * stacktop = 0;

void strstack_use_buffer(char*mem, size_t mem_size) {
    M = mem;
    M_size = mem_size;
    stacktop = mem; 
}

void strstack_clear() {
    stacktop = M;
}

int strstack_push(const char *s) {
    unsigned int length = 0;
    while (s[length] != 0) {
        ++length;
    } 
    if (((stacktop - M) + length + 1) <= M_size) {
        while(*s != 0 &&) {
            *stackstop = *s;
            ++stackstop;
            ++s
        }
        *stackstop = *s;
        stacktop += 1;
    } else {return 0;}
}

const char *strstack_pop() {
    if (stacktop == M) {
        return 0;
    }
    --stackstop;
    while (stackstop != M && *(stacktop -1) != 0) {
            --stackstop;
    } 
    return stacktop;
}



