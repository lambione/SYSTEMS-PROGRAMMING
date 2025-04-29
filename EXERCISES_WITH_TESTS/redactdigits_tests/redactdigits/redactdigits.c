#include<stdio.h>

int redact_digits(char * s) {
    int m = 0;
    while (*s != 0) {
        if (isdigit(*s)) {
            m = 1;
            *s = '#';
            s++;
        }
        else {
            s++;
        }
    }
    return m;
}
