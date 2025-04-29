#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

    
    //if there are no parameters or "" then program must output "No target characters specified" in a single output line 


    //argc > 2 are all file names , so cunted pointed characters also fromm here 

    // format output filaname ci : ni  balbalbal

    //ci is the ith targeted character  and ni is the times that character appeared 

    //error ? then print Error reading file filename, continue easy 

#if 0
int main(int argc, char * argv[]) {
    //first parameter is a string containing the set of target characters that must be counted
    if (argc <= 1) { //if arguments are less than 1 and 
        printf("No target charachters specified\n");
        return 1;     } 
    if (argc > 1) {
        const unsigned char * target = (const unsigned char *)argv[1]; //hint by carza, this is just letting us use the first argument as a string 
        if (isspace(*target)) {
            printf("No target charachters specified\n");
            return 1; 
        }

        int count = 0;
        while(target) {
            ++count;
        }
        target = (const unsigned char *)argv[1];

        if (argc <= 2) {
            int arr[count]; //counter array for the targets
            for(char c=getchar(); c != EOF; c=getchar()) {
                int j = 0;
                while (target) {
                    if (c == target) {
                        arr[j] = arr[j] + 1; //add the fact that it was seen 
                        ++target;
                        ++j;
                    } else {
                        ++j;
                    }
                }
                target = (const unsigned char *)argv[1]; 
            }

            printf("stdin ");
            for (unsigned int i = 0; i<count; ++i) {
                printf("%c:%s", *target, arr[i]);
            }
        }
    }
}
#endif


#if 1
const unsigned char * target;	/* string of target characters (bytes) */

/* vector of occurrence counters for each char/byte */
size_t C[256];	

void output_error(const char * fname) {
    printf("Error reading file %s\n", fname);
}

void output_count(const char * fname) {
    printf("%s", fname);
    for (const unsigned char * t = target; *t != 0; ++t)
        printf(" %c:%zu", *t, C[*t]);
    printf("\n");
}

int do_count(FILE * f) {
    for (int i = 0; i < 256; ++i)
        C[i] = 0;
    int c;
    while ((c = fgetc(f)) != EOF) 
        C[c] += 1;
    return (ferror(f) == 0);
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        printf("No target characters specified.\n");
        return 1;
    } 
    target = (const unsigned char *)argv[1];
    if (argc < 3) {
        if (!do_count(stdin))
            output_error("(stdin)");
        else
            output_count("(stdin)");
    } else {
        for (int i = 2; i < argc; ++i) {
            FILE * f = fopen(argv[i], "r");
            if (!f) {
                output_error(argv[i]);
            } else {
                if (!do_count(f))
                    output_error(argv[i]);
            else
                output_count(argv[i]);
            fclose(f);
            }
        }
    }
}

#endif

    


    


