#include <stdio.h>
#include <limits.h>

int main() {
    float i;
    float minimum = INT_MAX;
    float maximum= INT_MIN;
    float sum = 0;
    int numbers = 0;
    float average = 0;
    while (scanf("%f", &i) > 0) { 
            numbers += 1;
            sum += i;
        if (i < minimum){
            minimum = i;
        }
        if (i > maximum){
            maximum = i;
        }
    }
    if (numbers != 0) {
    average = sum / numbers;
    printf("%f %f %f\n",minimum,average,maximum);
    }
}

