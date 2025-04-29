#include<stdio.h>
#include<assert.h>

#include "lines.h"

int main() {
    char buffer[MAX_LINE_SIZE];
    while(fgets(buffer,MAX_LINE_SIZE,stdin) ) {  //fgets takes a char*s, int size that's the size of array, and the stream  and returns a pointer, initial if ok otherwise null pointer
        assert(add_line(buffer));
    }
    const char * line;
    for(line = pop_line(); line != 0; line = pop_line()){
        printf("%s", line)
    }
    clear();

}    