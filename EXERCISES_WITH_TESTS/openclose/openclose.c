#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>



#if 0
    //the m=command line string input is given as command line 
    unsigned int i = argc;

    char * stack[1000 + 1];
    char * ss = stack;  //they both point to the same array 

    for (unsigned j=0; j<i;++j) {
        char prev = argv[j]; //first place of the string
        char * str = argv[j];
        ++str; //we start frokmsecond place 
        while (str) {
            *ss = *str;
            ss += 2;
            str += 2;
            
            
        }
    } 
#endif



static char closing_char (char c, const char * OC) {
    for (unsigned i = 0; OC[i] != 0; i += 2)
        if (OC[i] == c)
            return OC[i+1];
    return 0;
}

int main (int argc, char *argv[]) {
    const char * OC = "()[]{}";
    char line[1001];
    if (argc > 1)
	    OC = argv[1];
    char * t = line;
    for (int c = getchar(); c != EOF; c = getchar()) {
        if (c == '\n') {
            *t = 0;
            printf("%s\n", line);
            t = line;
        } else if (t == line) {
            *t++ = c;
        } else if (closing_char(*(t - 1), OC) == c) {
            --t;
        } else {
            *t++ = c;
        }
    }
}









#if 0

size_t nbytes = 0;
// char *A;

char *A = (char *) malloc(1000*sizeof(char));

//read a line from stdin

while ( (getline(&A, &nbytes, stdin)) >= 0) {
    
    // stack magic
    
    printf("\n");


    for (int j = 0; j < nbytes; j++){
        printf("%c", A[j]);
    }
    memset(A, 0, 1000);
    nbytes = 0;
} 
free(A);
}
// process the line that is read or currently being read
//print processed line


#endif 



