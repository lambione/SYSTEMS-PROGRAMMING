#include <stdio.h>
#include <ctype.h>

int main () {
    int word = 0; /*counter for the words*/
    int mark = 0; /*if it is a 0 then there is a space, if it is a 1 than there is a character*/
    int d = getchar();
    while(d != EOF) {
        if(isspace(d)) {
            if(mark==1) { /*if the mark was 1 it means that before we found the space there was a character which means a word*/
                mark = 0; /*we place mark to 0 because we found a space*/
                word += 1; /*we founded a word so we update counter*/
            }
        }
        else{
            mark = 1; /*if there is no space it means that there is a character so we will always place mark equals to 1*/
        }
    }
    if (mark == 1) { /*if we exit the loop and mark is equal to 1 it means that there is a word that has not been counted*/
            word += 1; /*we add it here then*/
        }
    printf("%d\n", word); 
    }
    
