#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// need to strip directory names and extensions, only image names file 
// jpg, .jpeg, .png, .tiff, and .tif this are the names
int validation_extension(char line[]) {
    const char * extensions[] = {"jpg", "jpeg", "png", "tiff", "tif"};
    char * dup = strdup(line);
    if (!dup) return 0;
    char * token = strtok(dup, "/");
    while(token) {
        unsigned length = 0;
        if (length == 0 && token[length] == '.') {
            goto skip;
        }
        while(token[length] != 0) {
            if(token[length] == '.') {
                ++length;
                for(unsigned int i = 0; i<5; ++i) {
                    char * t = token + length;
                    // printf("%c ciao\n", *t);
                    // printf("%s\n", extensions[i]);
                    // printf("%d\n", strncpy(t,extensions[i] ,3));
                    if (strncmp(t,extensions[i],3) == 0) { //if they compare as a valid image extension 
                        for(unsigned int j = 0; (token[j] != '.' || (token[j+1] != 'p' && token[j+1] != 'j' && token[j+1] != 't')); ++j) {
                            putchar(token[j]);
                        }
                        printf("\n");
                        break;
                    }
                }
            }
            ++length;
        }
        skip :  
            token = strtok(NULL, "/");
    }
    return 1;

    free(dup);
}


int main(int argc, char * argv[]) {

    char line[1001];
    FILE * f;
    unsigned int command = 0;
    if (argc > 1) {
        f = fopen(argv[1], "r");
        if (!f) {
            if(!fgets(line,1000,stdin)) 
                return 0;
        } else {
            if (!fgets(line,1000,f)) {
                command = 0;
                fgets(line,1000,stdin);
            } else {
                command = 1;
            }
        }
    }

    // we already read the first line
    validation_extension(line);
    if (command == 1) {
        char * c = fgets(line,1000,f);
        while(c) {
            validation_extension(line);
            c = fgets(line,1000,f);
        }
        return 1;

    } else if (command == 0) {
        while(fgets(line,1000,stdin)) {
            validation_extension(line);
        }
        return 1;
    }
    return 1;

}