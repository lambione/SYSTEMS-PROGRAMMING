#include<stdio.h>
#include<assert.h>
#include<ctype>

int print_numbers(const char *input) {
    unsigned int counter = 0;
    while (*input != 0) {
        if (isdigit(*input) || ((*input == '-' || *input == '+') && isdigit(input[1]))) {
            ++counter;
            do {
                putchar(*input);
                ++input;
            } while (isdigit(*input));
            putchar('\n');
        } else 
            ++input;
        }
        return counter;
        // } else (isdigit(*input)) {  /*was on the right path*/
        //     flag = 1;
        //     counter += 1;
        //     while(isdigit(*input)) {
        //         putchar(*input);
        //         ++input;
        //     }
        //     putchar('/n');
        //     ++input;
        // }
    }

int main(str[] args) {
    assert(print_numbers("abc123xyz-7//443.2") == 4);
}

