#include<stdio.h>

int string_lt(const char *a , const char *b) {
    // boolean value corresponding to the lexicographical order relation
    unsigned int i = 0;
    for(i = 0; a[i] != 0 && b[i] != 0 ; ++i) {
        if (a[i] < b[i]) {
            return 1;
        }
        if (a[i] > b[i]) {
            return 0;
        }
        return a[i] < b[i];
    }
}

void sort_strings(const char * input, char * output, unsigned int n) {
    const char *s[1000];
    for(unsigned int i=0;i<n;++i) {
        s[i] = input;
        while(*input != 0) {
            ++input;
        }
        ++input;
    }

    // insrtion sort of s 
    for(unsigned int i=1;i<n;++i) {
        unsigned int j = i;
        while (j>0 && string_lt(s[j], s[j-1])) {
            // swap s[j] with s[j-1]
            const char *tmp = s[j];
            s[j] = s[j-1];
            s[j-1] = tmp;
            --j;
        }
    }
    for(unsigned int i=0 ; i<n ; ++i) {
        // copy s[i] into output
        for(const char *p = s[i]; *p != 0; ++p, ++output) {
            *output = *p; 
        }
        *output = 0;
        ++output;
    }

}