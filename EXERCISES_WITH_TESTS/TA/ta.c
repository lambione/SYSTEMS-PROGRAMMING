#include <stdio.h>
#include <stdlib.h> 

static struct course {
    char title[201]; 
    char semester;
    unsigned int taNumber;
    struct course * next;
} C = {0,0,0,0};

static struct people {
    char name[50];
    unsigned int Fav;
    unsigned int Sav;
    struct people * next;
} P = {0,0,0,0};

int processCourse (const char * courseFile) {
    FILE * f = fopen(courseFile, "r");
    if (!f) return 0;
    char line[205];
    while(fgets(line,205,f)) {
        // printf("%s\n", line);
        struct course * new = malloc(sizeof(struct course));
        if (!new) {
            fclose(f);
            return 0;
        }
        unsigned counter = 0;
        //copied the name
        for (unsigned int j = 0; line[j] != 0; ++j) {
            if (line[j] != ',') {
                (new->title)[j] = line[j];
                ++counter;
            } else if (line[j] == ',') {
                ++counter;
                break;
            }
        }
        new->semester = line[counter];
        counter += 2;
        new->taNumber = atoi(&(line[counter]));
        //link new element
        new->next = C.next;
        C.next = new;
    }
    fclose(f);
    return 1;
}


int processPeople(const char * peopleFile) {
    FILE * f = fopen(peopleFile, "r");
    if (!f) return 0;
    char line[55];
    while(fgets(line,55,f)) {
        struct people * new = malloc(sizeof(struct people));
        if (!new){
            fclose(f);
            return 0;
        } 
        unsigned counter = 0;
        //copied the name
        for (unsigned int j = 0; line[j] != 0; ++j) {
            if (line[j] != ',') {
                (new->name)[j] = line[j];
                ++counter;
            } else if (line[j] == ',') {
                ++counter;
                break;
            }
        }
        new->Fav = atoi(&(line[counter]));
        counter += 2;
        new->Sav = atoi(&(line[counter]));
        // link new element
        new->next = P.next;
        P.next = new;
    }
    fclose(f);
    return 1;
}

int print_function() {
    for (struct course * iterCourse = C.next; iterCourse; iterCourse = iterCourse->next) {
        printf("%s\n", iterCourse->title);
        if (iterCourse->taNumber == 0) continue;
        for (struct people * iterPeople = P.next; iterPeople; iterPeople = iterPeople->next) {
            if(iterCourse->taNumber == 0) break;
            if (iterCourse->semester == 'S' && iterPeople->Sav >= 1) {
                printf("%s, ", iterPeople->name);
                --iterPeople->Sav;
                --iterCourse->taNumber;
            }
            if(iterCourse->semester == 'F' && iterPeople->Fav >= 1) {
                printf("%s, ", iterPeople->name);
                --iterPeople->Fav;
                --iterCourse->taNumber;
            }
        }
        if (iterCourse->taNumber > 0) printf("(INCOMPLETE)");
        printf("\n");
    }
    return 1;
}

void deleteAllocated() {
    /*need to delete*/
    if (!C.next) goto nextOne;
    while(C.next) {
        struct course * tmp = C.next->next;
        free(C.next);
        C.next = tmp;
    }

    nextOne :
        if (!P.next) return;
        while(P.next) {
            struct people * tmp = P.next->next;
            free(P.next);
            P.next = tmp;
        }
}

void printusage() {
    printf("run in this way -> ./progeamName courseFile peopleFile\n");
}

int main(int argc, char * argv[]) {

    if (argc < 3) {
        printusage();
        return 0; // we need parameters to assign ta's to courses
    }

    int cs = processCourse(argv[1]);
    int pp = processPeople(argv[2]);
    
    if (cs == 0 || pp == 0) {
        deleteAllocated();
        printf("an error occured\n");
        return 0;
    }

    print_function();
    deleteAllocated();
    return 1;
}