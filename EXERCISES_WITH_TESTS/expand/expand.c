#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// hints : fgets,fopen, fclose strncmp

static struct patterns {
    // this is the pattern p->t
    //remember that it should be in order 
    char * p;
    char * t;
    struct patterns * next;
} pt = {0,0,0};

int read_rules(char * filename) {

    FILE * file = fopen(filename, "r");
    if(!file) return EXIT_FAILURE;

    struct patterns * last = pt;

    unsigned int in_pattern = 0; //used as a flag to say if we are reading a part of the word still
    unsigned int added = 0;
    char line[2001];
    while(fgets(line,2000,file)) {

        if (!strchr(line,':')) { 
            //when we find a line that doesn't have a : we simply skip dat shit
            in_pattern = 0;
            added = 0;
            continue;
        }

        if(in_pattern == 1) goto no_allocation;

        //now we create a pattern structure to store the pattern we just found
        struct pattern * pp = malloc(sizeof(struct patterns));
        if (!pp) return EXIT_FAILURE;

            char * token = strtok(line,':');

            if(strlen(token) > 0) {
                if(in_pattern == 1) in_pattern = 0;
                else in_pattern = 1;
                //allocate space for the string
                char * s = strdup(token);
                if(!s) return EXIT_FAILURE;
                pp->p = s;
                pp->next = 0;
            } else if () {

            }
            token = strtok(NULL,':'); // will stop at the end
            if(in_pattern == 1) {
                
            }

        //check if struct hasn't been updated
        if(added == 0) {
            //now I will need to add it at the end of the linked list because order matters
            last->next = pp;
            last = pp;
            added = 1;
        }
    }
}

int main(int argc, char * argv[]) {
    // with no argument the program reads the default file RULES 
    if (argc < 2) {
        read_rules("RULES");
    } else {
        for(unsigned int i = 1;i<argc;++i) {
            read_rules(argv[i]);
        }
    }

}