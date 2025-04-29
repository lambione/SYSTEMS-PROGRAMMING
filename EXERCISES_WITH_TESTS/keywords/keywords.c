#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// extract words, word = sequence of characters recognised by isalpha() ciao is valid cia34 the word is cia
// frequency are between 0 and 100

// output format must be sorted in descending order of frequency. If two
// words have the same frequency, the order must be lexicographical


//this linked list will be tramutaed into array 
struct word {
    char * w;
    unsigned int count;
    double frequencies;
    struct word * next;
};

struct file {
    char * filename;
    struct word * words;
    unsigned int word_number; 
};

/*returne 1 if word already exists otherwise returns 0*/
int check_existance_update(char * word, struct file * f) {
    for(struct word * iter = f->words; iter; iter = iter->next) {
        if (strcmp(word, iter->w) == 0) {
            //we found the word so we update the structure 
            ++iter->count;
            return 1;
        }
    }
    //if we are here the word doesn't exist so we add it 
    struct word * newWord =(struct word *) malloc(sizeof(struct word));
    if(!newWord) return -1;
    char * ww = (char *)malloc(strlen(word) + 1);
    if (!ww) {
        free(newWord);
        return -1;
    }
    newWord->w = ww;
    newWord->count = 1;
    newWord->frequencies = 0;
    newWord->next = 0;

    //add to linked list
    struct word * tmp = f->words;
    f->words = newWord;
    newWord->next = tmp;
    return 0;
}

void delete_allocated(struct file * ff) {
    free(ff->filename);
    while(ff->words) {
        free(ff->words->w);
        struct word * tmp = ff->words->next;
        ff->words = ff->words->next;
        free(tmp);
    }
    free(ff);
}

void print_function(struct file * file, unsigned int l, unsigned int h, unsigned int type, unsigned int inverted) {
    //now we need apsolutely to create an array to work better with sorting 
    unsigned int counter = 0;
    for(struct word * iter = file->words; iter; iter = iter->next) {
        ++counter;
    }

    if (counter == 0) return; //we print nothing

    //otherwise we create an array where to place all our structures;
    struct word * word_arr = malloc(sizeof(struct word)*counter);
    if (!word_arr) return;
    unsigned int k = 0;
    for(struct word * it = file->words; it; it = it->next) {
        word_arr[k] = *it;
    }

    // now we got all our words in our array 
    // now remember we still didn't calculate frequencies which is something we need to do
    // now with array access is easy, we also know how long is the array  
    for(unsigned int l = 0; l < counter; ++l) {
        word_arr[l].frequencies = word_arr[l].count / file->word_number;
    }

    //now frequencies are all up to date 
    //now sort
    //up until here it was complexity n now we destroy our beauty making it n^2
    //this is sorting by frequence
    for (unsigned int a = 0; a < counter; ++a) {
        for(unsigned int b = 1; b < counter; ++b) {
            if (inverted == 1) {
                if (word_arr[b].frequencies < word_arr[a].frequencies)
                    goto compute;
            } else {
                if(word_arr[b].frequencies > word_arr[a].frequencies)
                    goto compute;
            }

            continue;

            compute :
                struct word tmp = word_arr[a];
                word_arr[a] = word_arr[b];
                word_arr[b] = tmp;
        }
    }

    //now sort by lexicographical order 
    for (unsigned int a = 0; a < counter; ++a) {
        for(unsigned int b = 1; b < counter; ++b) {
            if (strcmp(word_arr[b].w,word_arr[a].w) == -1) {
                struct word tmp = word_arr[a];
                word_arr[a] = word_arr[b];
                word_arr[b] = tmp;
            }
        }
    }

    //now everything is done sorted and ready to be printed
    printf("%s", file->filename);
    for(unsigned int p = 0; p < counter; ++p) {
        if (type == 1) {
            printf(" %f:%s",word_arr[p].frequencies, word_arr[p].w);
        } else if (type == 0) {
            printf(" %s", word_arr[p].w);
        }
    }

    //now deallocate the array
    free(word_arr);

}



int processFile(const char * f, unsigned int l, unsigned int h, unsigned int simple, unsigned int fancy, unsigned int inverted) {
    FILE * fileOpened = fopen(f, "r");
    if (!fileOpened) return 0;  //no one asked to print an error

    
    struct file * file = (struct file *)malloc(sizeof(struct file));
    if (!file) goto errors;

    //allocate memory for the name
    char * fname = (char *)malloc(strlen(f) + 1);
    if (!fname) goto errors;
    strcpy(fname,f);
    file->filename = fname;

    file->words = 0;
    file->word_number = 0;

    unsigned official_counter = 0;
    unsigned old_point = 0;
    unsigned lsst_word = 0;
    for(int c = fgetc(fileOpened); ; c = fgetc(fileOpened)) {
        if (c == EOF) goto word_process;    
        if(isalpha(c) != 0) {
            ++official_counter; 
            continue;
        }

        word_process :
            //if we are here it means that the word is over so what we need to do is to
            unsigned int word_len = official_counter - old_point; 
            rewind(fileOpened);
            fseek(fileOpened,old_point,SEEK_SET);
            //now that we moved the file pointer back we can read the word and put it into an array of length that we know
            char word[word_len + 1];
            unsigned int j = 0;
            for(int ch = fgetc(fileOpened); j < word_len; ch = fgetc(fileOpened)) {
                word[j] = ch;
                ++j;
            }
            printf("%s", word);
            word[word_len + 1] = 0; //place terminator

            //now we got our word we can hit a 
            int check = check_existance_update(word, file);
            if (check == 0) 
                ++file->word_number;
            if (check == -1)
                goto errors;
            
            old_point = official_counter;
            if(c == EOF) break;
    }

        

    //now comes the beauty with the actual printing of the stuff
    //we give a unique parameter to the print function so that we understand if we wanna print fancy or simple
    // fancy = 1
    // print = 0
    if (simple == 1) {
        print_function(file,l,h,0,inverted);
    } else {
        print_function(file,l,h,1,inverted);
    }

    //close file deallocate and u are finished
    delete_allocated(file);
    fclose(fileOpened);
    return 1;

    errors:
        fclose(fileOpened);
        if (file) delete_allocated(file);
        return 0;

}



int main(int argc, char * argv[]) {

    // default frequencies are :
    unsigned int lFrequence = 10; //lower bound
    unsigned int hFrequence = 90; //upper bound
    unsigned int change = 0; //flag to say if frequencies were changed

    unsigned int simple = 1; //default is simple format to print
    unsigned int fancy = 0; //non-default

    unsigned int inverted = 0;

    //this loop we checks the command line arguments to see what formats we should print and we store them into the right formats
    for (int i = 1; i < argc; ++i) {  
        if (strcmp(argv[i], "low=") == 0) {
            char * tmp = argv[i] + 4;
            lFrequence = atoi(tmp);
            if (change != 0) 
                hFrequence = 100;
            change = 1;
        } else if (strcmp(argv[i], "high=") == 0) {
            char * tmp = argv[i] + 5;
            hFrequence = atoi(tmp);
            if (change != 0)
                lFrequence = 0; 
            change = 1;
        } else if (strcmp(argv[i], "-f") == 0) {
            fancy = 1;
            simple = 0;
        } else if (strcmp(argv[i], "-r") == 0) {
            inverted = 1;
        }else if (strcmp(argv[i], "--") == 0) {
            //when we find this we will need to scan the command line up until the next format information
            ++i ;
            while (i < argc) {
                //if we are here it means that we are reading all argyments as a file, and for every file we will need to call it with the same format requests 
                processFile(argv[i], lFrequence, hFrequence, simple, fancy, inverted);
                ++i;
            }
            //
            break;
        } else {
            while( (strcmp(argv[i], "low=") != 0) && 
                    (strcmp(argv[i], "high=") != 0) && 
                    (strcmp(argv[i], "-f") != 0)  && 
                    (strcmp(argv[i], "--") != 0) && 
                    (strcmp(argv[i], "-r") != 0) && 
                    i < argc) 
                {   
                processFile(argv[i], lFrequence, hFrequence, simple, fancy, inverted);
                if(++i >= argc) {
                    return 1;
                }
            }
            if(i >= argc) {
                return 1;
            } else {
                --i;
            }
         }
     }
    
}

