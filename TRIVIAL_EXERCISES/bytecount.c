#include <stdio.h>

int main () {
    int c = 0;
    while((getchar()) != EOF) {
        c += 1;
    }
    printf("%d\n", c);

}