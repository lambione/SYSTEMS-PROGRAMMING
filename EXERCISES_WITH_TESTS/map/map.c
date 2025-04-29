#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

struct map {
    char * key;
    void * value;
    struct map * next ;
};

static struct map * mp = 0;

int map_init(){
    struct map * m = malloc(sizeof(struct map));
    if (!m) return 0;
    m->key = 0;
    m->value = 0;
    m->next = 0;
    mp = m;
    return 1;
}; /* initializes the map */

void map_shutdown() {
    while(mp->next) {
        struct map * tmp = mp->next->next;
        free(mp->key);
        free(mp->value);
        free(mp->next);
        mp->next = tmp;
    }
    free(mp);
}

int map_clear() {
    while(mp->next) {
        struct map * tmp = mp->next->next;
        free(mp->key);
        free(mp->value);
        free(mp->next);
        mp->next = tmp;
    } 
}   
/* removes all elements */
int map_put(const char * key, void * value) {
    for(struct map * iterator = mp->next; iterator; iterator = iterator->next) {
        if (strcmp(iterator->key,key) == 0) {
            iterator->value = value;
            return 1;
        }
    }
    //if we arrive here it means that we need to add this new mapping
    //we malloc it and we add it at the beginning
    struct map * new = malloc(sizeof(struct map));
    if(!new) return 0;
    char * s = malloc(strlen(key) + 1);
    if (!s) {
        free(new);
        return 0;
    }
    strcpy(s,key); 
    new->key = s;
    new->key = s;
    new->value = value;
    //link it at the beginning
    new->next = mp->next;
    mp->next = new;

}
void * map_get(const char * key) {
    for(struct map * iterator = mp->next; iterator; iterator = iterator->next) {
        if (strcmp(iterator->key,key) == 0) {
            return iterator->value;
        }
    }
    return NULL;
}

void map_start_iteration() {
    for(struct map * iter = mp->next; iter; iter = iter->next) {
        /*boh*/
    }
}

int map_iterate(const char ** key, void ** value) {
    if(*key && *value) return 0;
    /*do something for this map*/
    return 1;
}

int main() {

}