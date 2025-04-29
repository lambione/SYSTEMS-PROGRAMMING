#include "lists.h"
//can't use any external library

//they operate on lists of integers 
//no additional memory only objects passed as parameters
//

#if 0

//takes an array of n(count) lists (pointers to the first element of a linked list) and returns a single list by concatening all the elements of the n lists in the given order some lists might be empty
struct list * concatenate_all(int count, struct list * lists[]) {

    struct list *p;

    for(unsigned int i=0; i<count-1; ++i ) {//we iterate on the lists array with n(count) iterations
        struct list * concat = lists[i]; //we intialize a pointer to first element of the lists 
        p->next = concat;
        if (lists[i]) { //this checks that lists exist 
            while(concat->next) { //we say that we iterate up untile next exists (which means we go to the end of the list)
                concat = concat->next;  //we say that the pointer to struct list p will now be pointing to the second element, third el....
            }
            p = concat; //we hold the last position 

            //when we are here me reached the end of the list 
        }
    }

    //now we concatenated everything so we return 
    return lists[0]; //we simply return pointer to the first lists that linked to all the others;

#endif



struct list * concatenate_all(int count, struct list * lists[]) {
    struct list * result = 0;
    struct list ** last = &result;
    for (int i = 0; i < count; ++i) {
	    struct list * l = lists[i];
        if (l) {
            *last = l;
            while (l->next) 
                l = l->next;
            last = &(l->next);
        }
    }
    return result;
}

struct list * merge_sorted(struct list * a, struct list * b) {
    struct list * result = 0;
    struct list ** last = &result;
    while (a || b) {
        if (a != 0 && (b == 0 || a->value <= b->value)) {
            *last = a;
            last = &(a->next);
            a = a->next;
        } else  {
            *last = b;
            last = &(b->next);
            b = b->next;
        }
    }
    return result;
}








    #if 0  //code written before rereading the notes (total shit)

    struct list * l; // first list          


    if (*lists != NULL) {
        l = *lists;
    }  
    if (*lists == NULL) {

        while (*lists = NULL) {
            ++lists;
            --count;
        }
        l = *lists;
    }

    while (count > 0) { //we decrease it every time
        if (*lists != NULL) { // if lists exists

            //decrease counter 
            --count;

            struct list * p = * lists; //now we are pointing to the linked list inside the array lists

            while(*p->next != NULL) {
                *p = *p->next;//iterate through the list to reach the end 
            }

            //if we are here technically it means that we reached the list has at least an element 
            //now we concatenate it with the next one
            ++lists;
            if(*lists != NULL) {

                *p->next = * (*lists);   //we said that the previous list is now pointing to the one after 

            }
        }  else { //if listsdoesn't exist 
            //just go to the next one
            ++lists;
    
        }
    }

    return l; //returning pointer to struct concatenated list 

}

    #endif 



#if 0

//takes two lists that aRe sorted in non-decreasing order and returns a single one sorted, don't remove values, if values are repeated, both should be there 
struct list * merge_sorted(struct list * a, struct list * b) {

    struct list * merged = a; //we point to a 
    struct list * prev;

    while(*a->next != NULL || *b->next != NULL) {
        if (*a->next != NULL) {
            if (*b-> next != NULL) {
                if (*a->value < *b->value) {
                    *prev = *a;
                    *a = *a->next; //we go to next element if a is smaller than b                   ///to finish
                } else if (*a->value > *b->value) {
                    struct list * tmp = *b->next //next element in b
                    *b->next = a;
                    *prev->next = *b;
                    *b = *tmp; 
                }
            }
        }

    }
#endif 

