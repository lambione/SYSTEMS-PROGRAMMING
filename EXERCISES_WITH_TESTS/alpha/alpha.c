#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void bit_print(int b) {
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'};
    printf("%c", arr[b]);
}



int main(int argc, char * argv[]) {

    unsigned int enc_dec = 0; //0 we encode, 1 we decode

    if (argc > 2) 
        return EXIT_FAILURE;
    if (argc == 2) {
        if (strncmp(argv[1], "-d",2) != 0) 
            return EXIT_FAILURE;
        if (strlen(argv[1]) > 2)
            return EXIT_FAILURE;
        enc_dec = 1;
    }

    unsigned int counter = 80;
    if (enc_dec == 0) {
        //this is we run it in encode mode 
        for(int c = getchar(); c != EOF; c = getchar()) {
            if ((isalpha(c) != 0)){
                if (c == 'Q'){
                    if (counter == 1) {
                        putchar('Q');
                        putchar('\n');
                        counter = 80;
                        putchar('Q');
                        --counter;
                    } else if (counter == 0) {
                        putchar('\n');
                        counter = 80;
                        printf("QQ");
                        counter -= 2;
                    } else {
                        printf("QQ");
                        counter -= 2;
                    }
                } else {
                    if (counter == 0) {
                        putchar('\n');
                        counter = 80;
                    }
                    putchar(c);
                    --counter;
                }
            } else {
                //we arrive here and we will never have counter = 0
                if(counter == 0) {
                    putchar('\n');
                    counter = 80;
                } else if (counter == 1) {
                    putchar('Q');
                    putchar('\n');
                    counter = 80;
                } else if (counter > 1) {
                    putchar('Q');
                    --counter;
                }
                // followed by two characters that are encode numbers between 0 and 15 that are the most and least significant four bits of b,
                int b_most = c / 16;
                int b_least = c % 16;
                
                bit_print(b_most);
                --counter;

                if (counter == 0) {
                    putchar('\n');
                    counter = 80;
                }

                bit_print(b_least);
                --counter;
            }
        }
    } else if (enc_dec == 1) {
        //we need to decode it 
        for(int c = getchar(); c != EOF; c = getchar()) {
            if(counter == 0) {
                counter = 80;
                putchar('\n');
            }
            putchar(c);
            --counter;
        }
    }
    if(counter == 80 || enc_dec == 1) return EXIT_SUCCESS;
    else putchar('\n');
    return EXIT_SUCCESS;

    

}