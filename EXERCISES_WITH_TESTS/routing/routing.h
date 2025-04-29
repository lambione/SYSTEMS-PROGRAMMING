#ifndef ROUTING_H_INCLUDED
#define ROUTING_H_INCLUDED

/* clear the database of points and deallocate all objects within the
   library */
extern void routing_clear();

/* defines or changes the coordinates of a point */
extern int routing_set_point(const char * name, double x, double y);

/* compute the total distance traveled in the given path.  A path is a
   comma-separated list of point names.  The result must be -1 if any
   one of the points is undefined. */
extern double routing_total_distance(const char * path);

#endif
