#include "rowing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// only one club
struct club {
    struct club_members * members; 
    struct boats * boats;
};

struct boats {
    const char * name;
    unsigned int max;
    unsigned int curr_number_crew;
    unsigned int available; // 0 not available, 1 available
    unsigned int excursion_counter;
    unsigned int boat_km;
    struct boats * next;
};

struct club_members {
    const char * name;
    unsigned int km; //keep truck of total km
    unsigned int in_excursion; //flag to say if is already in an excursion 0 is in, 1 is not
    unsigned int excursion_number;
    struct club_members * next;
};

// in an excursion there can only a boat
struct excursion {
    // we place just one boat per excursion
    struct club * club;
    const char * boat_name;
    struct club_members * m; //array of names
};


// creates a new club an returns a valid pointer to an empty club, return null ptr uf it fails 
struct club * create_club () {
    struct club * c = malloc(sizeof(struct club));
    if(!c) {
        return c;
    }
    c->members = 0; //null ptr 
    c->boats = 0;
    return c;
}

// destroys the given club object and releases all its allocated resources.
void destroy_club (struct club * c) {

    while(c->boats) {
        struct boats * tmp = c->boats;
        c->boats = c->boats->next;
        free((void *)tmp->name);
        free(tmp);
    }

    while(c->members) {
        struct club_members * tmp = c->members;
        c->members = c->members->next;
        free((void *)tmp->name);
        free(tmp);
    }

    free(c);
}

// adds boat by name to club c and maximum crew size, boat with max of four can take between 1 and four persons on an excursion, return 1 on success and 0 in fail, 
// two boats with the sam ename on same club is wrong 
int add_boat (struct club * c, const char * name , unsigned int max_crew) {
    struct boats * b = malloc(sizeof(struct boats));
    if (!b) {
        return 0;
    }

    char * n = malloc(sizeof(strlen(name)) + 1);
    strcpy(n,name);
    n[strlen(name) + 1] = 0; // null terminator

    b->name = n;
    b->max = max_crew;
    b->curr_number_crew = 0;
    b->available = 1;
    b->excursion_counter = 0;
    b->boat_km = 0;
    b->next = 0; //null ptr

    if (!c->boats) {
        c->boats = b;
    } else {
        struct boats * iter = c->boats;
        while (iter)  {
            if (strcmp(b->name, iter->name) == 0) {
                return 0;
            }
            iter = iter->next;
        }      
        // link at the beginning the new element
        b->next = c->boats ;
        c->boats = b; 
    }
    return 1;

}

// adds a person to club c. Persons are also identified uniquely by name within a club there can't be person with the same name 
int add_person (struct club * c, const char * name) {
    struct club_members * member = malloc(sizeof(struct club_members));
    if (!member) {
        return 0;
    }
    char * n = malloc(sizeof(strlen(name) + 1));
    strcpy(n,name);
    n[strlen(name) + 1] = 0;
    
    member->name = n;
    member->km = 0;
    member->excursion_number = 0;
    member->next = 0; //null ptr

    if (!c->members) {
        c->members = member;
    } else {
        struct club_members * iter = c->members;
        while (iter)  {
            if (strcmp(member->name, iter->name) == 0) {
                return 0;
            }
            iter = iter->next;
        }      
        // link at the beginning the new element
        member->next = c->members ;
        c->members = member; 
    }
    return 1;

}

// create an excursion object to prepare an excursion within club c, return valid pointer to a new excursion object 
struct excursion * create_excursion (struct club * c) {
    struct excursion * exc = malloc(sizeof(struct excursion));
    if (!exc) {
        return exc;
    }

    exc->club = c;
    exc->boat_name = 0; 
    exc->m = 0;

    return exc;
}

// assigns the named boat to the excursion e
// the boat remains assigned to the excursion until the excursion is closed or canceled. Return 0 if
// the boat does not exist or is not available because it is currently assigned to another excursion.
int use_boat (struct excursion * e, const char * name) {
    struct boats * iter = e->club->boats;
    while (iter) {
        if (strcmp(name, iter->name) == 0) {
            if (iter->available == 0) 
                return 0;
            e->boat_name = iter->name; 
            return 1;
            }
            iter = iter->next;
    }
    return 0;


}

// assigns the named person as a crew member for the excursion e
// In this case, the person is assigned and remains assigned to the given excursion until
// that excursion is canceled or closed.
// Return 0 if the excursion does not yet have an assigned boat,or if the maximum crew capacity of the boat has already been reached, , or if the named person does not belong to the club, 
// or if the named person has already been added to the crew of another excursion.
int add_crew (struct excursion * e, const char *name) {
    if (!e->boat_name || e->club->boats->max == e->club->boats->curr_number_crew) {
        return 0;
    } 
    struct club_members * iter = e->club->members;
    while (iter)  {
        if (strcmp(name, iter->name) == 0) {
            if(iter->in_excursion == 0)
                return 0;
            if (e->m) {
                // add to excursion
                // add to boat 
                // add person to counter 
                // add person in excursion
                struct club_members * new_m = malloc(sizeof(struct club_members));
                new_m->name = iter->name;
                new_m->km =0;
                new_m->in_excursion = 0;
                new_m->excursion_number = 0;

                new_m->next = e->m;
                e->m = new_m;

                e->club->boats->curr_number_crew += 1;

                return 1;
            } else {
                struct club_members * new_m = malloc(sizeof(struct club_members));
                new_m->name = iter->name;
                new_m->km =0;
                new_m->in_excursion = 0;
                new_m->excursion_number = 0;

                new_m->next = 0;
                e->m = new_m;

                e->club->boats->curr_number_crew += 1;

                iter->in_excursion = 1;

                return 1;
            }
        }
        iter = iter->next;
    }
    return 0;   
}

// confirms that the given excursion has ended successfully with the given distance k traveled (in kilometers). The excursion object e is also destroyed and all its allocated
// resources are properly released
// The excursion object e is also destroyed and all its allocated resources are properly released
// Return 0 when the given excursion has not been set up properly, with a valid boat and a crew of at least one person. In this case, the excursion object remains valid
int close_excursion (struct excursion * e, unsigned int k) {
    if (!e->boat_name || !e->m) {
        return 0;
    }

    struct boats * iter = e->club->boats;
    while (iter)  {
        if (strcmp(e->club->boats->name, iter->name) == 0) {
            if(iter->curr_number_crew < 1) 
                return 0;
            else {
                iter->boat_km += k;
                iter->excursion_counter += 1;
                iter->curr_number_crew = 0;
                iter->available = 1;
                break;
            }


        }
        iter = iter->next;
    }
    // now we need to give evryone the km and destroy the excursion
    struct club_members * iter_m = e->club->members;
    while(iter_m) {
        if (strcmp(e->m->name, iter_m->name) == 0) {
            iter_m->km += k;
            iter_m->excursion_number += 1;
            iter_m->in_excursion = 1;

            struct club_members * tmp = e->m;
            e->m = e->m->next;
            free(tmp);
            // restart again because maybe members are not in order 
            iter_m = e->club->members;
            continue;
        }
        iter_m = iter_m->next;
    }

    // now we need to destroy the excursion
    free(e);

    return 1;

}

// given exursion is cancelled detsroy everything 
void cancel_excursion (struct excursion * e) {
    while(e->m) {
        struct club_members * tmp = e->m;
        e->m = e->m->next;
        free(tmp);
    }
    // now we need to destroy the excursion
    free(e);

}

int get_crew_excursions (struct club * c, const char * name ) {
    struct club_members * iter_m = c->members;
    while(iter_m) {
        if (strcmp(name, iter_m->name) == 0)
            return iter_m->excursion_number;

        iter_m = iter_m->next;
    }
    return -1;
}

int get_crew_kilometers (struct club *c , const char *name ) {
    struct club_members * iter_m = c->members;
    while(iter_m) {
        if (strcmp(name, iter_m->name) == 0)
            return iter_m->km;

        iter_m = iter_m->next;
    }
    return -1;
}

int boat_available (struct club *c, const char *name) {
    struct boats * iter_m = c->boats;
    while(iter_m) {
        if (strcmp(name, iter_m->name) == 0) {
            if (iter_m->available == 1) {
                return 1;
            } else {
                return -1;
            }
        }
        iter_m = iter_m->next;
    }
    return -1;
}
int get_boat_excursions (struct club *c , const char *name) {
    struct boats * iter_m = c->boats;
    while(iter_m) {
        if (strcmp(name, iter_m->name) == 0)
            return iter_m->excursion_counter;

        iter_m = iter_m->next;
    }
    return -1;
}
int get_boat_kilometers (struct club *c , const char *name ) {
    struct boats * iter_m = c->boats;
    while(iter_m) {
        if (strcmp(name, iter_m->name) == 0)
            return iter_m->boat_km;

        iter_m = iter_m->next;
    }
    return -1;
}
