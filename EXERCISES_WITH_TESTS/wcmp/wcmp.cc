#include <ctype.h>
#include <string.h>
#include "wcmp.h"

int wcmp(const char * a, const char * b) {

    unsigned int same = 1;
    unsigned int bookmark = 0;
    for(unsigned int i = 0; a[i] != 0; ++i) {
        if (isalpha(a[i]) != 0 && isalpha(b[i]) != 0) {
            ++bookmark; 
            if (a[i] == b[i]) {
                same = 1;
            } else if (a[i] < b[i]){
                return -1;
            } else {
                return 1;
            }
        } else if ((isalpha(a[i]) != 0) && (isalpha(b[i]) == 0)) {
            // if(isspace(b[i] != 0)) {
            //     ++b;
            //     --i;
            // }
            ++bookmark;
            same = 0;
            return 1;
        } else if ((isalpha(a[i]) == 0) && (isalpha(b[i]) != 0)) {
            // if (isspace(a[i]) != 0) {
            //     ++a;
            //     --i;
            // }
            ++bookmark;
            same = 0;
            return -1;
        } else if (isalpha(a[i]) == 0 && isalpha(b[i]) == 0){
            ++bookmark;
            same = 1;
            continue;
         }// else {
        //     if (isspace(a[i]) != 0) {
        //         ++a;
        //     }
        //     if(isspace(b[i] != 0)) {
        //         ++b;
        //     }
        // }
    }

    if (same == 1 && (isalpha(b[bookmark]) != 0)) {
        return -1;
    } else if (same == 1 && (isalpha(b[bookmark] == 0))) {
        for(unsigned int j = 0; b[j] != 0; ++j) {
            if (isalpha(b[j]) != 0) 
                return -1;
        }
        return 0;
    } else {
        if (same == 1 || (strlen(a) == 0 && strlen(b) == 0)) {
            return 0;
        } else {
            return -1;
        }
    }
}