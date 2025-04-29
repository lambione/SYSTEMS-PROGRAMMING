#include<stdio.h>
#include<stdlib.h>

//mine
#if 0
int main(int argc, char *argv[]) {

    char arr[61]; //where we are gonna store the values 

    int min = 0;
    int max = -1;

    if (argc > 2) {
        // min = atoi(argv[1]);
        max = atoi(argv[2]);
    }
    if (argc > 1) {
        min = atoi(argv[1]);
    }
    
    //char * arr_sp = &(arr[0]); //initialize it at the same level of arr
    int j =0;
    int length = 0;
    for(int c=getchar(); c!= EOF;c = getchar()) {
        if (c == '\n') {
            if (length >= min && ( max < 0 || length <= max)) {
                // *arr_sp = 0;
                arr[j] = 0;
                printf("%s", arr);
                if (length > j)
                    printf("...");
                printf("\n");
            }
            length = 0;
            j = 0;
            // * arr_sp = &(arr[0]);
        } else {
            if (j <= 60) { // length
                arr[j] = c;
                ++j;
                #if 0
                *arr_sp = c;
                ++arr_sp;
                #endif
            }
            ++length;
        }
    }
    return 0;
}
#endif



//carza does it better 
#if 1 
int main (int argc, char * argv[]) {
    int min = 0;
    int max = -1;
    char line[60+1];

    if (argc > 2)
	    max = atoi (argv[2]);
    if (argc > 1)
	    min = atoi (argv[1]);

    int i = 0;
    int len = 0;
    for (int c = getchar(); c != EOF; c = getchar()) {
	    if (c == '\n') {
	        if (len >= min && (max < 0 || len <= max)) {
		        line[i] = 0;
		        printf("%s", line);
                if (len > i)
                    printf("...");
		        printf("\n");
	        }
            len = 0;
            i = 0;
        } else {
            if (i < 60) {
                line[i] = c;
                ++i;
            }
            ++len;
	    }
    }
    return 0;
}

#endif