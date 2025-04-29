#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void format_flush_left(char * begin, char * end) {
    char * iter = begin; //initialized to begin
    char * placer = begin;
    int reading = 0;
    int began = 0; //flag to say if we already started to print the first character
    while(iter != end) {
        if(!isalpha(*iter) && began == 0 && !ispunct(*iter)) {
            ++iter;
        } else {
            began = 1;
            if (isalpha(*iter) || ispunct(*iter)) {
                if(reading == 0) {
                    
                }
                reading = 1;
                //swap
                char tmp = *placer;
                * placer = *iter;
                *iter = tmp; 
                ++iter;
                ++placer;
            } else {
                if (!isalpha(*iter)) {
                    // char tmp = *placer;
                    // * placer = *iter;
                    // *iter = *placer; 
                    reading = 0;
                    ++iter;
                    ++placer;
                }
            }
        }
    }
}


void format_flush_right(char * begin, char * end);
void format_justified(char * begin, char * end);

int main() {

    char s[] =   "  It ain't over 'til it's over.   ";
    format_flush_left(s,s+35);
    printf("%s\n", s);

}