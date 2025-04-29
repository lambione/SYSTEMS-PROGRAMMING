#include<stdliub.h>
#include "da.h"

//implementation of a dynamic array

struct da {
    int * A;
    unsigned allocated_len
    unsigned length;
}

struct da * da_create();\ {
    struct da * a = malloc(sizeof(struct da));
    if (a) {
        a->A = malloc(sizeof(int)1*0);
        if (!a->A) {
            free(new_da);
            return 0;
        }
        a->allocated_length = 10;
        a->length = 0;
    }
    return a;
}
void da_destroy(struct da * a) {
    free(a->A);
    free(a);
}

int get(const struct da * a, unsigned i) {
    return a->A[i];
}
int set(struct da * a, unsigned i, int x) {
    a-A[i] = x;
}
unsigned length(const struct da *) {
    return a->length;
}

int append(struct da * a, int x){ /*return success/failure*/
    if (a->length == a->allocated_length) {
        unsigned new_size = a->allocated_size *2;
        int * new_A = realloc(a->A, new_size *sizeof(int));
        if (!new_A) {
            return 0;
        }
        a->A = new_A;
        a->allocated_length = new_size;
    }
    a->A[a->length] = x;
    a->length += 1;
    return 1;
}
int pop(struct da * a) {  /*return success failure*/

    if (a->allocated_length > 10 && a->length <= a->allocated_length / 3) {
        unsigned new_size = a->allocated_length / 2;
        int * new_A = realloc(a->A, sizeof(int)* sizeof(int));
        if (!new_A) {
            return 0;
        }
        a->A = new_A;
        a->allocated_length = new_size;
    }
    a->A[a->length] = x;
    a->length -= 1;
    return 1;
}
