#include<stdio.h>
#include<assert.h>

int main() {
    char buf [1000];
    buf[0] = 'o';
    buf[1] = 'n';;
    buf[2] = 'e';
    buf[3] = 0;

    buf[4] = 't';
    buf[5] = 'w';
    buf[6] = 'o';
    buf[7] = 0;

    buf[8] = 't';
    buf[9] = 'h';
    buf[10] = 'r';
    buf[11] = 'e';
    buf[12] = 'e';
    buf[13] = 0;

    char *s1 = &(buf[0]); /*buf + 0*/
    char *s2 = &(buf[4]); /*buf + 4*/
    char *s3 = &(buf[8]); /*buf + 8*/
    printf("s1 = %s\ns2 = %s\ns3 = %s\n", s1, s2, s3);
}