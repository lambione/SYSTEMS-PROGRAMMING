#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>

int main (int argc, char *argv[]){
    const char *filename = "default.input";
    if (argc > 1)
        filename = argv[1];
    FILE * f = fopen(filename,"r");
    if (!f) {
        fprintf(stderr, "couldn't open file %s\n", filename);
        return EXIT_FAILURE;
    }
    unsigned count = 0;
    for(int c = fgetc(f); c!= EOF; c=fgetc(f);) 
        ++count;
    printf("%u\n", count);
    fclose(f);
}