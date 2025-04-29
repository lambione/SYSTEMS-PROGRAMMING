#include<stdio.h>
#include<ctype.h>

int line_to_args (char * argv[], int max_count, char * line) {
    int i = 0;
    int flag = -1;  /*1 ur in a component, -1 u r not*/
    while (*line != 0) { /*just to skip first spaces*/
        if (!isspace(*line) && flag == -1) {
            flag = 1;
            if (i < max_count) {
                argv[i] = line;
                i++;
            }
            line++;
        } else if (!isspace(*line) && flag == 1){
            line++;
        } else if (flag == 1 && isspace(*line)) {
            flag = -1;
            *line = 0;
            line++;
        } else if (flag == -1 && isspace(*line)) {
            line++;
        }
    }
    return i;
}