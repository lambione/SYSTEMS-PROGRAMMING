#include <stdio.h>
#include<ctype.h>
#include<assert.h>

int main() {
#if USING_MALLOC
    unsigned *C = malloc(sizeof(unsigned)*26*26);
    assert (C);
#else
    unsigned C[26][26];
#endif

#if USING_MALLOC

    for (unsigned i = 0; i<26*26;++1)
        C[i] = 0;

#else 
    for(unsigned i = 0; i<26;++i)
        for(unsigned j=0; j<26;++j)
            C[i][j] = 0;

#endif

    int curr,prev = -1;
    for(curr = getchar(); curr != EOF; curr = getchar()){
        if (isalpha(prev) && isalpha(curr)){
            curr = toupper(curr);
#if USING_MALLOC
            C[(prev - 'A')*26 + curr - 'A'] += 1;
#else 
            C[prev - 'A'][curr - 'A'] += 1;
#endif

        }
        prev = toupper(curr);
    }
    for(unsigned r = 0; r<26; ++r){
        int c_max = 0;
        for (unsigned c = 1; c<26; ++c){
#if USING_MALLOC
            if (C[26*r][c_max] < C[26*r][c])
                c_max = c;
#else
            if (C[r][c_max] < C[r][c])
                c_max = c;
        }
        if (C[r][c_max] != 0) {
            printf("%c%c", 'A' + r,'A' + c_max);  //'A' is the at the beginning of the matrix
        }
#endif
    }
}