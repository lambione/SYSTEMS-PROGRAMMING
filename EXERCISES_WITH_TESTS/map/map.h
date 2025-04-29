#ifndef MAP_INCLUDED
#define MAP_INCLUDED

extern int map_init();		/* initializes the map */
extern void map_shutdown();	/* destroys the map */

extern int map_clear();		/* removes all elements */

extern int map_put(const char * key, void * value); /* associates key with value */
extern void * map_get(const char * key);	    /* returns the value associated with key */

extern void map_start_iteration();
extern int map_iterate(const char ** key, void ** value);

#endif
