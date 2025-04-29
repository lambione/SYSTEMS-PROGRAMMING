#include<stdio.h>
#include<ctype.h>
#include<string.h>


// If format_paragraphs is non-zero (true), 
// then the text is considered as a sequence of para-
// graphs separated by empty lines.

// If format_punctuation is non-zero (true),
// then the spacing before some punctuation char-
// acters are deleted

struct t_opts {
    int format_paragraphs; //0 or 1
    int format_punctuation; // 0 or 1
    int max_line_len;
};

int t_format(char * t, struct t_opts * opt) {

    //BASIC NORMALIZATION
    //the processing of the file must be done directly on the t string
    //removes empty lines at the beginning and at the end 
    //multiple spaces become 1 space
    
    //default option
    if(opt->format_paragraphs == 0 && opt->format_punctuation == 0) {

        unsigned int foundCharacter = 0; //0 we still didn't find the foirst character
        char * empty = "";

        for(unsigned int i = 0; t[i] != 0; ++i) {
        if(isspace(t[i]) == 0) {
            foundCharacter = 1;
            continue;
        }
        for (unsigned int j = i+1; t[j] != 0; ++j) {
            if(isspace(t[j]) == 0) {
                if(t[i] == '\n' && foundCharacter == 1) ++i;
                t[i] = t[j];
                if (i != j) t[j] = *empty;
                foundCharacter = 1;
                if(isspace(t[j+1]) != 0) {
                    ++i;
                    t[i] = ' ';
                }
                break;
            } else if (t[i] == '\n' && foundCharacter == 1) {
                if(t[j] == '\n') {
                    t[i] = t[j];
                    t[j] = *empty;
                }
            }
        }
    }
    return 1;
    } else if (opt->format_paragraphs == 1 && opt->format_punctuation == 0) {

        unsigned int foundCharacter = 0; //0 we still didn't find the foirst character
        char * empty = "";

        unsigned separated = 0; //0 means no line yet for paragraph, 1 already got a line for paragraph 
    

        for(unsigned int i = 0; t[i] != 0; ++i) {
        if(isspace(t[i]) == 0) {
            foundCharacter = 1;
            separated = 0;
            continue;
        }
        for (unsigned int j = i+1; t[j] != 0; ++j) {
            if(isspace(t[j]) == 0) {
                if(t[i] == '\n' && foundCharacter == 1) ++i;
                separated = 0;
                t[i] = t[j];
                if (i != j) t[j] = *empty;
                foundCharacter = 1;
                if(isspace(t[j+1]) != 0) {
                    ++i;
                    t[i] = ' ';
                }
                break;
            } else if (t[i] == '\n' && foundCharacter == 1) {
                if(separated == 0){
                    separated = 1;
                    i = j;
                    break;
                };
                if(t[j] == '\n') {
                    t[i] = t[j];
                    t[j] = *empty;
                }
            }
        }
    }
    for (unsigned int k = 0; t[k] != 0; ++k) {
        if(t[k] == '\n') {
            unsigned found = 0;
            unsigned l = k + 1;
            while(t[l] != 0) {
                if(isspace(t[l]) == 0) {
                    found = 1;
                    break;
                }
            }
            if (found == 1) { /*we found a character*/
                found = 0;
            } else {
                t[k] = 0;
            }
        }
    }
    return 1;
    }



    // [c][i][a][][c][][\n][][][][\n][][i][a][\n][][][][][][][\n]

}