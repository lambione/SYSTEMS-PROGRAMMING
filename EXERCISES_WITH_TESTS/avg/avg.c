#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<assert.h>


float average_positives(const int * begin, const int * end) {
    int count = 0;
    int all = 0;
    while (begin != end) {
        printf("%d\n", *begin);
        if ((*begin - 0) > 0) {
            ++count; 
            all = all + *begin;
        }
        ++begin;
    }
    if (count == 0) {
        return -1;
    } else {
        int average = all / count;
        return average;
    }
}


int main() {
    int buf1[] = { 0, -1.0, 0, 2, -2, 0, 4 }; 

    assert(average_positives(buf1, buf1 + 3) == -1);
    assert(average_positives(buf1, buf1) == -1);
    assert(average_positives(buf1 + 3, buf1 + 3) == -1);
    assert(average_positives(buf1 + 2, buf1 + 3) == -1);
    assert(average_positives(buf1 + 2, buf1 + 4) == 2);
    assert(average_positives(buf1 + 2, buf1 + 7) == 3);
    assert(average_positives(buf1, buf1 + 4) == 2);
    assert(average_positives(buf1, buf1 + 3) == -1);
    assert(average_positives(buf1 + 4, buf1 + 4) == -1);
    assert(average_positives(buf1 + 3, buf1 + 4) == 2);
    assert(average_positives(buf1, buf1 + 4) == 2);
    assert(average_positives(buf1, buf1 + 7) == 3);

    printf("TESTS PASSED.\n");
}