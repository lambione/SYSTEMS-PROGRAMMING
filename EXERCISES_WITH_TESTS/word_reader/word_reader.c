#include <stdio.h>
#include <ctype.h>

#include "word_reader.h"


#define WORD_MAX_LEN 1024


const char * read_next_word(FILE * file) {
    char * empty = "";

    if (!file) return empty;

    char word[WORD_MAX_LEN + 1];

    unsigned int j = 0;
    for(int c = fgetc(file); c != EOF && j < WORD_MAX_LEN; c = fgetc(file)) {
        if(isalpha(c) != 0) {
            word[j] = c;
            ++j;
            continue;
        }
        //if we are here we break
        break;
    }
    ++j;
    word[j] = 0;
    printf("%s\n", word);
    for(unsigned j = 0; j<WORD_MAX_LEN; ++j) {
        word[j] = *empty;
    }
}

int main(int argc, char * argv[]) {

    FILE * f = fopen(argv[1], "r");
    if(!f) return 0;


    for(unsigned int l = 0;l<5; ++l) {
        read_next_word(f);
    }
    
}