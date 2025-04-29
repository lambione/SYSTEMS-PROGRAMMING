#include<stdio.h>

void print_array(const int *begin, const int * end) { 
    while(begin!= end) {
        printf("%d\n", *begin);
        ++begin;
    }
}