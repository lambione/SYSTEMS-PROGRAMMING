#include<stdio.h>
#include <string.h>

int i; /*this variable is an object, stored somewhere in memory*/
int A[10]; /*array is an object that contains object, since it is an array those objects are one after the other in memory*/
struct { /*defines a particular struct objects, composed by two other objects in this case*/
    float x;
    float y;
} point; /*name of the struct*/

/*types are not stored in memory*/
/*type is a set of accaptable value*/

// int main() {
//     printf("size of i %zu\n", sizeof(I));
// }


/*objects data in memory .....*/
// value
// type
// lifetime
// address
// size



itn main() {
    int i = 5;
    float f = 5.0; /*sizeof(f) == 4 bytes*/
    double x = 5.0;
    float g;

    printf("sieof(M) = %zu\nsizeof(f) = %zu\n", sizeof(M), sizeof(f));
    unsigned char M[sizeof(f)];
    memcpy (M,&f,sizeof(f)) /*three parameter : destination, source, size*/
    for(int j=0;j<sizeof(M);j++) {
        printf("%u", M[j]);
        printf("\n")
    }
    memcpy (&g,M, sizeof(g));
}
