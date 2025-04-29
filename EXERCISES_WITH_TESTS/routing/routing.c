#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// NOTE: You should include the header file
#include "routing.h"


struct point {
    char * name;
    double x;
    double y;
  // NOTE: there is no need to check if you visited a point or not 
  //    unsigned int checked;
    struct point * next;
};

static struct database {
    struct point * p;
} db = {0};


void routing_clear() {
    while(db.p) {
        struct point * tmp = db.p;
        free(tmp->name);
        db.p = db.p->next;
        free(tmp);
    }
    /*don't need to free db because os manages that I think, because it is static*/
    // NOTE: Correct no need to free db, you free only heap allocated memory
}
/* defines or changes the coordinates of a point */
int routing_set_point(const char * name, double x, double y) {
    struct point * iter = db.p;
    // NOTE: This look will run forever 
    while(iter) {
        if (strcmp(name,iter->name) == 0) {
            iter->x = x;
            iter->y = y;
            return 1;
        }
	// NOTE: adding this to traverse the linked list
	iter = iter->next;
    }
    // if we are here it means that we didn't find it in the loop sowe need to add the point to the linked list
    struct point * pp =  malloc(sizeof(struct point));
    if (!pp) return 0;
    char * n = malloc(strlen(name) + 1);
    if (!n) {
      // NOTE: if the allocation of pp succeds and the allocation of n fails you
      // should deallocate pp otherwise you have a memory leak in case of error
      free(pp);
      return 0;
    }
    strcpy(n,name);
    pp->name = n;
    pp->x = x;
    pp->y = y;
    //pp->checked = 0;
    //now that a new object has been created we need to add it to the linked list
    struct point * tmp = db.p;
    db.p = pp;
    pp->next = tmp;
    return 1;
}

// NOTE: I just added a helper function to find points into the db
struct point *find_node(const char *name)
{
  for (struct point *p = db.p; p; p = p->next)
    if (strcmp(p->name, name) == 0)
      return p;
  return NULL;
}

/* compute the total distance traveled in the given path. A path is a
comma-separated list of point names. The result must be -1 if any
one of the points is undefined. */
double routing_total_distance(const char * path) {

    double total_distance = 0;
    // I need to duplicate it because it is const 
    char * dupPath = strdup(path);
    // NOTE: if you go to error here you will call free(dupPath), so you will be calling
    // free on NULL which is not a good practice. Here, you can simply return since
    // the memory allocation failed so no memory was allocated
    //if (!dupPath) goto error;
    if (!dupPath) return -1.0;
    char * token = strtok(dupPath, ",");
    if (!token) return total_distance;

    struct point *p = find_node(token);
    if (!p) {
      free(dupPath);
      return -1.0;
    }

    double prev_x = p->x, prev_y = p->y;

    while ((token = strtok(NULL, ","))) {
      p = find_node(token);
      if (!p) {
	free(dupPath);
	return -1.0;
      }
      total_distance += sqrt((prev_x - p->x)*(prev_x - p->x) + (prev_y - p->y)*(prev_y - p->y));
      prev_x = p->x;
      prev_y = p->y;
    }
    return total_distance;

    // NOTE: to compute the distance you can use the euclidean distance (sqrt((x_1 - x_2)^2 + (y_1 - y_2)^2))
    // between the current point(token) and the point from the previous iteration (the previous position).
    // in the first iteration you have to start from the first point on the path so you extract
    // the first token. (above there is a possible implementation.
    
    /* while(token){ */
    /*     struct point * iterator = db.p; */
    /*     while(iterator) { */
    /*         if ((strcmp(token, iterator->name) == 0 ) && iterator->checked == 0) { */
    /*             iterator->checked = 1; */
    /*             double diff = iterator->x - iterator->y; */
    /*             if (diff < 0) { */
    /*                 diff = diff * -1; */
    /*                 total_distance += diff; */
    /*                 break; */
    /*             } else { */
    /*                 total_distance += diff; */
    /*                 break; */
    /*             } */
    /*         } */
    /*         iterator = iterator->next; */
    /*     } */
    /*     //point doesn't exist */
    /*     if (!iterator) */
    /*         goto error;  */

    /*     token = strtok(NULL, ","); */
    /* } */

    /* struct point * it = db.p; */
    /* while(it) { */
    /*     it->checked = 0; */
    /*     it = it->next; */
    /* } */

    /* return total_distance; */

    /* error : */
    /*     free(dupPath); */
    /*     struct point * i = db.p; */
    /*     while(i) { */
    /*         i->checked = 0; */
    /*         i = i->next; */
    /*     } */
    /*     return -1; */
}
