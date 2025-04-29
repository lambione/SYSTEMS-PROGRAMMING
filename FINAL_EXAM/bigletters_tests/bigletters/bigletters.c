#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct Big {
    char letter;
    unsigned int w;
    unsigned int h;
    unsigned int d;
    char * prt;  //what to print
    struct Big * next;
} B = {0,0,0,0,0};



int read_font(char * filename) {
    //each line of the font character starts with a letter 

    //open the file, check if fails
    FILE * f = fopen(filename, "r");
    if(!f) return 1;

    //approach idea
    /* iterate until we don't find the first part(find the :) tells us how long the rest after the : is, we allocate memory for that, we put it in the struct */
    for(int c = fgetc(f); c != EOF;c = fgetc(f)) {
        
        //initilaize struct where to store stuff
        struct Big * new = malloc(sizeof(struct Big));
        if(!new) {
            fclose(f);
            return 1;
        }
        //read from spec and put it into struct
        fscanf(f,"%c %d %d %d:", &(new->letter),&(new->w),&(new->h),&(new->d));

        //now linke it to linked list
        new->next = B.next;
        B.next = new;

        //now we need to get the remaining part and put it into prt
        unsigned int l = new->w * new->h; //we get the len of the next part by multiplying w*h
        //allocate memory for the string;
        char * pr = malloc(l + 1);
        if (!pr) {
            fclose(f);
            return 1;
        }
        for(unsigned int k = 0; k < l; ++k) {
            pr[k] = c;
            fgetc(f);
        }
        //put terminator
        pr[l] = 0;
        new->prt = pr; 
        //here we will have laready read the '\n'

        if(c == EOF) break;
    }

    fclose(f);
    return 0;

}

void print_line(unsigned int lineNumber, char * in, unsigned int baseLine) {
    //lineNUmber is the line we are printing from top
    for(unsigned int i = 0; in[i] != 0; ++i) {
        //flag that tell us if we found the character or not
        unsigned int found = 0;
        for(struct Big * iter = B.next; iter; iter = iter->next) {
            
            if(in[i] == iter->letter) {
                found = 1;
                //now we print the characters in depth of the first line
                //first check that te letter needs to print something on this line otherwise we skip it
                if((iter->h - iter->d) < lineNumber) {
                    for(unsigned int j = 0; j < iter->w; ++j) putchar(' ');
                    putchar(' ');
                    continue;
                } else {
                    //here we need to print something on this line
                    //height from baseline
                    unsigned int h = iter->h - iter->d;
                    int skip = h - lineNumber;
                    //start from where we need to print depending on what line we are in 
                    //do the number of iteration for the number of width we find
                    for (unsigned int l = (iter->w)*skip; iter->w ; ++l) {
                        putchar(iter->prt[l]);
                    }
                }
                putchar(' '); //this will be the space between the letters 
            }
        }
        if(found == 0) {
            //if we dind't find the character we put just one blank space if we are not in the base line, if we are in the base line we place the letter itself
            if(baseLine == 1) putchar(in[i]);
            else putchar(' ');
        }
    }

    //here we are done with the first line so we print an end of line
    putchar('\n'); 
}


int print_input(char *input) {
    //base case where font file is empty
    if(!B.next) {
        printf("%s\n", input);
        return 0;
    }
    //approach : double for loop O(n^2) sadly, read character per character from input string and everytime check in the linked list if we have any character matching, if match is found we need to print the width characters that should go in that line
    //we iterate over linked list, calculate max height above base line and max height below line
    unsigned int maxHeightAbove = 0;
    unsigned int maxHeightBelow = 0;
    //iterate over input
    for(unsigned int i = 0; input[i] != 0; ++i) {
        //iterate over linked list
        for(struct Big * iterator = B.next; iterator; iterator = iterator->next) {
            if(iterator->letter == input[i]) {
                //calculate height above baseline
                unsigned int above = iterator->h - iterator->d;
                if(maxHeightAbove < above) maxHeightAbove = above;  
                if(maxHeightBelow < iterator->d) maxHeightBelow = iterator->d;
            }
        }
    } 

    //now we know max height from above and below the baseline
    //theoretically now we need to print line by line the words so the approach is 
    //iterate through the input string and the linked list and print line by line
    unsigned baseline = maxHeightAbove - maxHeightBelow;
    unsigned int line_number = maxHeightAbove;
    //this loop will iterate over all lines above maxheight lines excluding base line
    while(line_number > 0) {
        print_line(line_number, input, 0);
        --line_number;
    }
    //now line_number is equal to base line so to 0, now we print base line and all letters not found in the 
    //should have called print_line with base line equal to 1
    print_line(line_number,input,1); //this will print the base line
    //now call it for negative lines under the baseline NO MORE TIME 

    return 0;
}

void deallocate_memory() {
    struct Big * iter = B.next;
    while(iter) {
        struct Big * tmp = iter->next;
        free(iter->prt);
        free(iter);
        iter = tmp;
    }
    //for the static one OS manages that
}



int main(int argc, char * argv[]) {

    //reading the font file either the default or the command line one
    if (argc < 2) {
        //check that no failure was found
        if (read_font("FONT") == 1) {
            deallocate_memory();
            return 1;
        }
    } else {
        //check that no failure ws found
        if (read_font(argv[1]) == 1){
            deallocate_memory();
            return 1;
        } 
    }

    //once we are here we have all formats in our structure 

    //reading the standard input max len 10000
    char line[1001];
    while(scanf("%s",line) != EOF) {
        //now we have what we need to print inside our lineso we need now to call the print function, REMEMBER check for failure
        if(print_input(line) == 1) return 1;
    };

    return 0;


    

}