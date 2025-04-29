#include<stdio.h>

int A[100];

void * p = &A; 

int i = 10;


int * function(){

for(unsigned int j = 0; j<10; j++) {
    *p = i;
    ++i;
    ++p;
}

return A;
}

int main() {
    function();
}