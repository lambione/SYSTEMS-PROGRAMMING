#include <stdio.h>

void print_diamond(unsigned int n) { /*we got a sequence of lines that is first n lines followed by n-1 lines */
    for (int i = 1; i <= n; ++i) {
        for (int j=0; j < n-i; ++j)
            putchar(' ');
        for (int j=0; j < 2*i-1; ++j)
            putchar('#');
        putchar('\n');
    }
    for (int i = n-1; i >= 1; --i) {
        for (int j=0; j < n-i; ++j)
            putchar(' ');
        for (int j=0; j < 2*i-1; ++j)
            putchar('#');
        putchar('\n');
    }
}

int main (int argc, char * argv[]) { /*argc is the number of parameters (length of the vector) and instead argv is the array*/
    // argv[0] argv[1] ..... argv[argc-1]
    if (argc < 2) {
        printf("error!! stupidd gimme a command-line argument\n ");
        return EXIT_FAILURE;
    }
    int n = strtoul(argv[1], NULL, 0);
    print_diamond(n);
}
