#include<stdio.h>

int twotimes(const char *s)  {
    unsigned int length = 0;
    while(*s != 0){
        ++length;
        ++s;
    }
    if (length % 2 == 1) {
        return 0;
    } 
    for(unsigned int i=0;i<length/2;++i) {
        if (s[i] != s[length/2 + i])
            return 0;
        return 1;
    }
}


int twotimes2(const char *s, const char *s_end)  {
    unsigned int length = s_end - s;
    if (length % 2 == 1) {
        return 0;
    }
    for(unsigned int i=0;i<length/2;++i) {
        if (s[i] != s[length/2 + i])
            return 0;
        return 1;
    }
}
