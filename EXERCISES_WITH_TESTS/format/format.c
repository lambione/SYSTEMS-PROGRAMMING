#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "format.h" 

void format_flush_left(char * begin, char * end) {
    unsigned int len = end - begin;
    char * empty = " ";
     //used to see if next one is a space
    // 0 is not a space
    // 1 is a space
    unsigned next = 0;
    for(unsigned int i = 0; i < len; ++i) {
        if(isspace(begin[i]) == 0) {
            continue; //it is not a space
        } else if (next == 1) {
            begin[i] = *empty;
            next = 0;
            continue;
        }
        for(unsigned int j = i+1; j < len; ++j) {
            //we enter here if we find a space 
            //we will replace it with the first character we find 
            //iterate until you don't find a space
            if (isspace(begin[j]) == 0){
                if (isspace(begin[j+1]) != 0) {
                    //if it is a space we finished a word
                    next = 1;
                }
                begin[i] = begin[j];
                begin[j] = *empty;
                break;  
            }    
        }
    }


}

void format_flush_right(char * begin, char * end) {
    unsigned int len = end - begin;
    char * empty = " ";

    //used to see if next one is a space
    // 0 is not a space
    // 1 is a space
    unsigned next = 0;
    for(unsigned int i = len; i > 0; --i) {
        if(isspace(begin[i]) == 0)  {
            continue; //it is not a space
        } else if (next == 1) {
            begin[i] = *empty;
            next = 0;
            continue;
        }
        for(unsigned int j = i-1; j > 0; --j) {
            //we enter here if we find a space 
            //we will replace it with the first character we find 
            //iterate until you don't find a space
            if (isspace(begin[j]) == 0){
                //if begin[j+1] exists check if it is a space
                if (isspace(begin[j-1]) != 0) {
                    //if it is a space we finished a word
                    next = 1;
                }
                begin[i] = begin[j];
                begin[j] = *empty;
                break;  
            }    
        }
    }
}

void format_justified(char * begin, char * end) {
    unsigned int len = end - begin;
    char * empty = " ";
    unsigned space_counter = 0;
    unsigned char_counter = 0;
    unsigned word_counter = 0;

    //now we need to count the words
    for (unsigned int i = 0; i<len; ++i) {
        if(isspace(begin[i]) != 0) {
            ++space_counter;
            continue;
        }
        else {
            for(unsigned int j = i; isspace(begin[j]) == 0 && j <len; ++j) {
                ++char_counter;
            }
            ++word_counter;
            ++space_counter;
        }
    }

    //now we know how many spaces we have and how many chars we have and how many words we have
    //if the word is just one we flush it left
    if (word_counter == 1) {
        format_flush_left(begin,end);
        return;
    }
    //if we have more instead
    //to calculate how many spaces we need between the words we do
    unsigned int trunked = 0;
    unsigned int spaceEach; 
    if (space_counter % word_counter == 0) {
        spaceEach  = space_counter / (word_counter + 1);
    } else {
        spaceEach = (int)(space_counter / word_counter);
        trunked = 1;
    }

    //carza move :
    // ha stra senso ora ho praticamente tutti gli spazi a sinistra
    format_flush_right(begin, end);

    unsigned next = 0;
    for(unsigned int i = 0; i < len; ++i) {
        if(isspace(begin[i]) == 0) {
            continue; //it is not a space
        } else if (next == 1) {
            for (unsigned k = 0; k < spaceEach; ++k) {
                begin[i] = *empty;
                ++i;
            }
            next = 0;
            continue;
        }
        for(unsigned int j = i+1; j > 0; ++j) {
            //we enter here if we find a space 
            //we will replace it with the first character we find 
            //iterate until you don't find a space
            if (isspace(begin[j]) == 0){
                if (isspace(begin[j+1]) != 0) {
                    //if it is a space we finished a word
                    next = 1;
                }
                begin[i] = begin[j];
                begin[j] = *empty;
                break;  
            }    
        }
    }
}


int main() {
    char s1[] = " ciaoanche se fuori tuttomake,e ci siamo anche aqui        s";

    format_justified(s1, s1+strlen(s1));
    printf("%s\n", s1);
    
}