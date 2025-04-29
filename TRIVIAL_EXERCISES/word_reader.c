#include<stdio.h>
#include<ctype.h>

#define WORD_MAX_LEN 1024

const char * read_next_word(FILE* a) {

    if (a == NULL) { //file is empty
        return 0;
    }

    char A[WORD_MAX_LEN];

    char * b = A;

    int i = 0;

    char next = fgetc(a)

    while(isalpha(next) == 0 && next != EOF){
        next = fgetc(a);
    }

    while(isalpha(next) && next != EOF && b-A < WORD_MAX_LEN ) {
        #if 0
        *b = next;
        b++
        #endif
        A[i] = next;
    c
    }
    return A;

}
