#include <stdlib.h>

#include "simplesets.h"


// io c'ho provato ma il carza zio pera io boh

/* Represents a set of objects. */
static struct ss {
    void * main_object; //can be any object
    void * next_object;
    struct ss * next;
} set = {0,0};

/* Create a set containing a single object. */
struct ss * ss_create_singleton() {
    struct ss * creation = malloc(sizeof(struct ss));
    if (!creation) return creation;
    creation->main_object = creation;
    creation->next_object = 0;
    creation->next = &set; //link it to the others
    creation = &set; //replace set at the beginning
    return creation;
}

/* Destroy all previously created sets. */
void ss_destroy_all() {
    struct ss * main = &set;
    while(main) {
        struct ss * tmp = main;
        main = main->next;
        free(tmp);
    }
}

/* Merge two sets into a single set.
*
* As a result, all the elements in X and Y belong to the same set,
* and both X and Y now refer to the same set.
*/
void ss_merge(struct ss * X, struct ss * Y) {
   if (X->main_object == Y->main_object) return; //they arealready merged
    struct ss * check = X;
    while (check->next_object) {
        check = check->next_object;
    } 
    check->next_object = Y; //we linked the new structure
    check = check->next_object;
    while (check) {
        check->main_object = X->main_object; //linka il main a tutti i nuovi 
    }

}

/* Test whether two sets are disjoint. */
int ss_disjoint(struct ss * X, struct ss * Y) {
    return (X->main_object != Y->main_object); //skill del carza
}