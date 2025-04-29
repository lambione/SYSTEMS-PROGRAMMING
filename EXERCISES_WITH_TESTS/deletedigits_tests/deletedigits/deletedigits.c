#include<stdio.h>
#include<ctype.h>

int delete_digits(char *s) {
    int foundach = 0;
    char *p = s;
    while(*s != 0) {
        if (isdigit(*s)) {
            foundach = 1;
        }
        else{
            *p = *s;
            p++;
        }
    s++;       
    }
    *p = 0;
    return foundach;
}