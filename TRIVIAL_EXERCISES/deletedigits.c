#include<stdio.h>

int delete_digits(char *s) {
    int foundach = 0;
    int l = 0; /* 0 if p is not occupied, 1 if it is occupied */
    char *p = p;
    while(*s != 0) {
        if (l == 0) {
            if (isdigit(*s)) {
                foundach = 1;
                l = 1;
                p = s;
                s++;
            }
        }
        else{
            if (l == 1) && (isdigit(*s) != 0){
                *p = *s;
                s = p;
                l = 0;
            }
        }
    }
    if (foundach != 0) {
        *p = 0;
        return 0;
    }
    else { 
        return 1;
    }

}