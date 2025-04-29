#ifndef DA_H_INCLUDED
#define DA_H_INCLUDED

/*implementing dynamic arrays of int */
struct da ;

struct da * da_create();
void da_destroy(struct da * a);

int get(const struct da * a, unsigned i);
int put(struct da * a, unsigned i, int x);
unsigned length(const struct da *);

int append(struct da * a, int x); /*return success/failure*/
int pop(struct da * a); /*return success failure*/


#endif 