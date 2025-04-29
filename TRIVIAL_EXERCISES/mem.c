#include<assert.h>

/*use malloc funcvtion to allocate meemory*/
// freee
//realloc 
/*also calloc exists but carza sayis to watch it alone which I'm scared to*/


//malloc
/*malloc takes a size and returns a VOID pointer to an area in memory that is good enough to store that memory size, size in bytesssss obviously*/
/*if malloc fails than malloc returns the null pointer*/


//free
/*free takes a void pointer and returns nothing, just releases memory*/
/*free takes a pointer that was returned by malloc or realloc*/
/*undefined behaviour if u use it with normal pointers*/

int * A;
A = malloc(10*sizeof(int));

assert (A!= null);

A[0] = 1
A[1] = 2

free(A); //this is okkkkkkkkkkkkkkkk juicy , we deallocate by freeing the pointer to THE OBJECT A, so to the start 
// if we free(A+1)  now A points to some point in the array that is not the start 

/*dynamic data structure that is the stack in file stack.c*/