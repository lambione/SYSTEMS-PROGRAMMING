#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


int processFile(char * filename, char * comment, int comment_len) {
    FILE * file;
    if(filename) {
        file = fopen(filename, "r");
    } else {
        file = stdin;
    } 

    if (!file) return 0;

    unsigned int total_lines = 0;
    unsigned int pure_comments = 0;

    char line[10001];
    while(fgets(line, 1000, file)) { /*places a 0 at the end*/
        ++total_lines;
        //now we have the line inside the line buffer 
        char * iter = line;
        unsigned int j = 0;
        while(j <  strlen(line) - comment_len) {
            if (strncmp(iter, comment, comment_len) == 0) {
                ++pure_comments;
                break;
            }
            if(isspace(*iter) == 0) 
                break;
            ++iter;
            ++j;
        }
    }
    if(filename) {
        printf("%s\t%u\t%u\n", filename,pure_comments,total_lines);
        fclose(file);
    } else {
        printf("(stdin)\t%u\t%u\n", pure_comments,total_lines);
    }

    // NOTE: this function should return an int (I guess you want to return 1
    // in case there was not error)
    return 1;
}


int main(int argc, char * argv[]) {

    char * comment = "//";
    int file_provided = 0;
    for(unsigned int i = 1; i < argc ; ++i) {
        if(strncmp(argv[i], "comment=", 8) == 0) {
            comment = argv[i] + 8; //copy the comment parameter
        } else {
	  // NOTE: just returning a failure status code in case of error
	  // (it's just a good practice)
	  if (!processFile(argv[i], comment, strlen(comment)))
	    return EXIT_FAILURE;
	  file_provided = 1;
        }
    }

    //in this case either we have no file in the input or maybe we have just the command parameter but we need to read from stdin
    // NOTE: this will run even if you call it as ./comments testfile.txt, not only
    // when you run it as ./comments comment='...'
    //if (argc < 3) {
    if (!file_provided) {
      // NOTE: just returning a failure status code in case of error
      // (it's just a good practice)
      if (!processFile(0, comment, strlen(comment)))
	return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}


