#include<stdio.h>
#include<stdlib.h>






// int j = 0; if we declare it here, it is a global variable and will exist forever

// int get_new_j() {
//     static int j = 0; //j is no more global
//     return ++j;
// }

// int main() {
//     int i; //this ill exist also at the end of the for loop
//     for (i = 0; i<10; ++i) {
//         int j;
//         for (j = 0; j<10; ++j) {
//             printf("%d", i + j);
//         }
//         printf("\n");
//     }
// }

int main() {
    for (i = 0; i<10; ++i) {
        int * jp = malloc(sizeof(int));
        if(i<5) {
            printf("%d", i);
        } else {
            for (*jp = 0; *jp<10; ++(*jp)) {
            printf("%d", i + *jp);
        }
        }
        printf("\n");
        free(jp);   
    }
}