/*print all bytes that it reads*/
#include <stdio.h>

int main () {
    for (int c = getchar(); c != EOF; c = getchar())
        printf("%d", c);
    printf("/n");
}