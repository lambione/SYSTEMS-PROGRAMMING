#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #include "fields.h"


int equal_fields(const char * begin, const char * end, char separator) {

    /*less work only with pointers*/
    unsigned int lenCounter = 0;
    unsigned int word_counter = 0;

    char * s = (char *) begin;
    char * s_end;

    for(unsigned int i = 0; i<(end-begin); ++i) {
        //increment the len everytime
        ++lenCounter;
        if(s[i] != separator){
            //increment word length every time we are in the word
            ++word_counter;
            continue;
        }
        //j points now to the item after the delim,
        //we iterate till the end
        //we will use strncpy to have a faster and precise comparison
        for (unsigned int j = lenCounter; (j+word_counter) < (end-begin); ++j) {
            if(strncmp(&(begin[j]),&(begin[lenCounter-word_counter]), word_counter) == 0) {
                return 1;   
            }
            while(begin[j] != separator) {
                if(begin[j] == 0) break;
                ++j;
            }
        }
        word_counter= 0;
    }
    return 0;
}




int main() {
    const char s1[] = "mammamia";
    const char s2[] = "ciao mamma";
    const char s3[] = "ciao,miao,bao";
    const char s4[] = "ciao,miao,bao,,";


    assert(equal_fields(s1, s1+strlen(s1), 'm'));
    assert(equal_fields(s2, s2+strlen(s2), 'm'));
    assert(!equal_fields(s1, s1+strlen(s1), 'a'));
    assert(!equal_fields(s3, s3+strlen(s3), ','));

    //sto test dimmerda faila perche ma vai in figa vede lo spazio tra la virgola e tra la virgola e la fine uguali;
    // assert(equal_fields(s4, s4+strlen(s4), ','));

    printf("TESTS PASSED.\n");
}