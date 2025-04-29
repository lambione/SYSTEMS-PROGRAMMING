#include<stdio.h>

void print_string (const char * c) { /*it's a pointer to a const char, sinnce it's a const we are not allowed to modify it*/
    for (int i = 0; s[i] != 0; ++i)
        putchar(s[i]);
}

while print_string(const char * s) {
    while (*s != 0) {
        putchar (*s);
        ++s;
    }
}

int main (int argc, char * argv[]) {   /*char * argv[] is an array of pointers we pass a pointer to a poiner to a char evvivaa le donneee */
    for (int i = 0; i < argc; ++i)
    printf("argv[%d] = \"%s\"\n", i,argv[i]);
}
