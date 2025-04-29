#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>

#include "words.h"

struct lines {
    char * line;
    int id;
    struct lines * next;
};

struct lines * lines_create() {
    struct lines * l = malloc(sizeof(struct lines));
    if (!l) {
        return l;
    }
    l->line = 0;
    l->id = 0;
    l->next = 0;
    return l;
}

void lines_destroy (struct lines * l) {
    while(l) {
        struct lines * tmp = l;
        l = l->next;
        free(tmp->line);
        free(tmp);
    } 
}

int add_line (struct lines * l, const char * line) {
    char * add_line = malloc(strlen(line) + 1);
    if (!add_line) {
        return -1;
    }
    strcpy(add_line, line);
    // add_line[strlen(line) + 1] = 0; already copies the 0 

    struct lines * tmp = l;
    // int id_counter = 0; counter is useless I can use tmp->id, was working anyway
    while(tmp->next) {
        // id_counter = tmp->id;
        tmp = tmp->next;
    }
    struct lines * new_line = malloc(sizeof(struct lines));
    if(!new_line) {
        // in case of error you're leaking the memory allocated for add_line, I need the free
        free(add_line);
        return -1;
    }
    new_line->line = add_line;
    new_line->id = tmp->id + 1; //i used counter here but we use tmp->id
    new_line->next = 0;

    tmp->next = new_line;

    return new_line->id;
}

int remove_line (struct lines * l, int id) {
    struct lines * tmp = l;
    while(tmp->next) {
        if (tmp->next->id == id) {
            // if(tmp->next->next) { useless check because pasquale explanation makes sense:
            // no need for this check if tmp->next->next is 0
            // after will simply be 0, so tmp will be the tail
            // of the list which is fine
            struct lines * after = tmp->next->next;
            free(tmp->next->line);
            free(tmp->next);
            tmp->next = after;
            // }
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

int match (struct lines * l, const char * output[], int max_output, const char * words) {
    // no need to allocate output, because it's a responsibility of the caller, grazie pasquale per la spiegaz, my big question was this one
    // tutto questo useless quindi 
    // output = (const char **)malloc(sizeof(const char *)*max_output);
    // if (!output) {
    //     return -1;
    // }
    // for (int i = 0; i < max_output; i++) {
    //     output[i] = NULL;
    // }

    // if no words are provided no match should be done
    // mi ero dimenticato sto edge case so scemo 
    if (strlen(words) == 0) return 0;

    // pasquale dice questo non sono molto sicuro ma ci fidiamo
    // The first node is going to be the "head" and it will contain line == NULL,
    // so start from the second node
    // invece di = l bisogna mettere =l->next;
    struct lines * tmp = l->next;
    unsigned int count = 0;
    char * strCopy = strdup(words);     // strdup uses a malloc underneath so you should check for failures ->pasquale ci evita i memory leak grazie pasqua'

    // dato che pasquale dice che usa malloc facciamo il check memory allocation failures
    if(!strCopy) {
        return 0;
    }
    char * token = strtok(strCopy, " ");
    while(tmp) {

        while (token != NULL) {
        
            if (strstr(tmp->line,token) == NULL) {
                // linee commentate pasqua suggerisce di metterle diretto nello skip quindi trap se fa ha ragione, dobbiamo freeare non lo sapevo
                // strCopy=strdup(words);
                // token = strtok(strCopy, " ");
                goto skip;
            } 
            token = strtok(NULL, " ");  
            
        }
        
        // when we are here token is null and tmp exists
        if (count < max_output) {
            output[count] = tmp->line;
            ++count;
            // tanto vengono fatti nello skip questi qui sotto, refactoring del pasquale letal assurdo pazzissimo
            // strCopy=strdup(words);
            // token = strtok(strCopy, " ");
        } else {
            break;
        }

        skip :
            free(strCopy);
            strCopy=strdup(words);
            if (!strCopy) return 0;
            token = strtok(strCopy, " ");
            tmp= tmp->next;
        
    }

    // arribati qui saremo passati dallo skip quindi dobbiamo freeare la duplication
    free(strCopy);

    // free(output);non serve piu ci ha aperto gli ochhi pasqua' sull'array
    return count;

}