#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s_table.h"

struct s_table {
    struct record * R;
};

struct record {
    char * rc;
    struct record * next;
};

/* Create and return a new s_table object.  Return 0 on failure. */
struct s_table * s_table_new() {
    struct s_table * table =(struct s_table *)malloc(sizeof(struct s_table));
    if(table) {
        table->R = 0;
    }
    return table;
}

/* Destroy the given s_table object and release all memory allocated by it. */
void s_table_delete(struct s_table * t) {
    s_table_clear(t);
    free(t);
}

void s_table_clear(struct s_table * t) {
    struct record * iter = t->R;
    while(iter) {
        struct record * tmp = iter->next;
        free(iter->rc);
        free(iter);
        iter = tmp;
    }
}

/* Add a record given by the give string with the given coordinates and description.
 * Return 0 on failure, 1 on success. */
int s_table_add_record(struct s_table * t, const char * begin, const char * end) {
    struct record * new_r = (struct record *)malloc(sizeof(struct record)); 
    if (!new_r) return 0;
    unsigned int len = end-begin;
    char * s =(char *)malloc(len); 
    if (!s) {
        free(new_r);
        return 0;
    }
    strcpy(s,begin);
    new_r->rc = s;
    //link it to the structure
    new_r->next = t->R;
    t->R = new_r;
    return 1;
}

/* Remove a record with the given coordinates and description.
 * Return 0 if not found, 1 if found (and removed). */
int s_table_remove_record(struct s_table * t, const char * begin, const char * end) {
    struct record * prev = 0;
    if(!prev) return 0;
    for(struct record * iter = t->R;iter;iter = iter->next) {
        if(end-begin == (long int)(strlen(iter->rc) + 1)){
            if(strcmp(begin, iter->rc)) {
                struct record * tmp = iter->next;
                free(iter->rc);
                free(iter);
                if(!prev) t->R = tmp;
                prev->next = tmp;
            }
        }
        prev = iter;
    }
    return 0;
}

/* Record processor: takes a record and returns an int
 */
typedef int (*feature_extractor)(const char * begin, const char * end);

/* Remove all the records that are selected by the given callback
 * function. A record is selected if the selector callback returns an
 * integer value that compares TRUE (i.e., != 0).
 *
 * Return the number of records that were removed. */
size_t s_table_remove_records(struct s_table * t, feature_extractor selector_callback) {
    size_t counter = 0;
    for(struct record * iter = t->R;iter;iter = iter->next) {
        if(selector_callback(iter->rc,iter->rc+strlen(iter->rc)) == 1) {
            s_table_remove_record(t,iter->rc,iter->rc+strlen(iter->rc));
            ++counter;
        } 
    }
    return counter;
}

/* Find a record with the maximal feature extracted by the given
 * callback function.  Copies the corresponding record in the given
 * buffer, defined by the record char pointer and the given max buffer
 * length.  Never copies more than record_max_len characters.
 *
 * Return the number of characters copied in the record buffer, or 0 
 * if there are no records in the table. */
size_t s_table_max_feature(struct s_table * t, feature_extractor feature_callback, char * record, size_t record_max_len) {
    struct record * found = t->R; //initially it is the first one
    int sameChar = 0; 
    for(struct record * iter = t->R;iter;iter = iter->next) {
        int readChar = feature_callback(iter->rc,iter->rc+strlen(iter->rc));
        if (readChar > sameChar) {
            sameChar = readChar;
            found = iter;
        }
    }

    record = (char *)malloc(record_max_len);
    if(!record) return 0;
    //now I need to copy characters into the buffer at most record_max_len
    unsigned int last = 0;
    for(unsigned int i = 0; i < record_max_len && i < strlen(found->rc); ++i) {
        record[i] = found->rc[i];
        ++last;
    }
    ++last;
    record[last] = 0;
    return last -1;

}

/* Print the table on the given FILE stream, one record per line, with
 * the records sorted in increasing order of the feature extracted by
 * the given callback function. */
void s_table_print_sorted(struct s_table * t, FILE * f, feature_extractor feature_callback) {
    for(struct record * iter = t->R;iter;iter = iter->next) {
        //no idea what to do here 
        fprintf(f,"ciao");
    }
}