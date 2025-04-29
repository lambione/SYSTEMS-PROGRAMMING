#include<stdio.h>

int concatenate(char * s, unsigned max_size, const char * s2) {
    int c = 0;
    while(*s != 0) {
        s += 1;
        c++;
    }
    while(c < max_size -1 && *s2 != 0){
        *s = *s2;
        s2++;
        s++;
        c++;
    }
    *s = 0;
    return *s2 == 0;
}