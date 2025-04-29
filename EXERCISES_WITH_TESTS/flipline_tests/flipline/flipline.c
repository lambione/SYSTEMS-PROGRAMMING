#include<stdio.h>

int main() {
    char line[1000];
    int c;
    int i = 0;
    for (;;) {
        c = getchar();
        if (c == EOF || c == '\n') {
            /*print the line in reverse*/
            /*first print the content of the line in reverse*/
            while (i > 0)
                putchar(line[--i]);
            /*then either print or return */
            if (c == EOF) {
                return 0;
            }
            putchar('\n');  
        } else if (i < 1000) {
            line[i] = c;
            i++;
            }
        }
    }