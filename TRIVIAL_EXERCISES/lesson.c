#include<stdio.h>
#include<assert.h>

unsigned int string3_length(const char *s) {/*const tells the compiler that s is a poineter to a constant char*/
/*an array is a sequence of CONTIGUOUS elements in memory*/
unsigned int length = 0;
while(*s != 0) {
    ++length;
    ++s;
}
return length;
}

unsigned int string2_length(const char *begin, const char *end) {
    return end-begin;
}

unsigned int string1_length(const char *begin, unsigned int length) {
    return length;
}



int main() {
    assert (string_length ("ciao") == 4);
}

void string3_print(const char *s) {
    while (*s != 0) {
        putchar(*s);
        ++s;
    }
}

void string2_print(const char *begin,const char *end) {
    while (begin != end) {
        putchar(*begin);
        ++begin;
    }

}

void string1_print(const char *begin,unsigned int length) {
    for (unsigned int i = 0; i <length; ++i)
        putchar (s[i]);  /*s[i]= (s + i)*/

}


int string3_compare(const char *a,const char *b) {
    while (*a == *b) {
        if (*a == 0 && *b == 0) {
            return 0;
        }
        ++a;
        ++b;
    }
    else if (*a < *b) {
        return -1
    } else {
        return  1
    }
}

int string3_compare(const char *a,const char *b) {
    for(;;) {
        if (*a < *b) 
            return -1;
        if(*a > *b) 
            return 1;
        if (*a == 0)
            return 0;
    }
}

int string3_compare(const char *begin1,const char *begin2,const char *end1, const char *end2) {
    while (b1 != e1 && b2 != e2) {
        if(*b1 < *b2) 
            return -1;
        if(*b1 >*b2)
            return 1;
        ++b1;
        ++b2;
    }
    if (b1==b2 && b2==b2) 
        return 0;
    if (b1 == e1)
        return -1
    return 1;
    
}