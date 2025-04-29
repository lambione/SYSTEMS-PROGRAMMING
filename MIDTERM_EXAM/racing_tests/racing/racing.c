#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

struct race {
    struct team * teams; //points to the first team in team linked list
    struct car * cars; //points to the first car in cars linked list
    struct driver * drivers; //points to the first driver in driver linked list

};

struct car {
    char * maker; //who made the car (ex ferrari)
    char * model; //model of the car
    struct driver * Driver; //driver of that car
    unsigned int hp; //horse power
    unsigned int price; //price of the car
    struct car * next_car; //need it for linked list of cars
};

struct team { 
    char * name;
    struct driver * drivers; //the team can have more than one driver so linked list of drivers
    struct team * next_team; //need it for linked list of teams

};

struct driver {
    char * name;
    struct team * Team; 
    struct driver * next_driver; //need it for linked list of drivers
};

static struct race * Race; 

int racing_init(const char * f) { //needs to return the total number of cars,drivers and teams read from the file

    Race = malloc(sizeof(struct race)); //I need this otherwise when I do clear on the base of what do I clear?, this will be the base of everything

    FILE * file = fopen(f,"r"); //part written by me but looked this morning in class with professor, this opens the file
    if (!file) { //if something went wrong
        fprintf(stderr, "couldn't open file %s\n", file); //print this message
        return EXIT_FAILURE; //and appropriate exit
    }
    //we are here it means that file was open successfully
    unsigned total_count = 0; //counter for the total numbers of cars,driversand teams


    //this is a better choic, i tried, but I have not time so I'll go on with my implementation
    #if 0
    char line[1000];
    fgets(line, 1000, file) //returns a string
    while (line!= 0) { //if it not the null pointer
        if (sscanf(line, "#%c%c%c", ) == 3 ) { //if we are in a line
            
        }
    }
    #endif


    #if 1
    for(int c = fgetc(f); c!= EOF; c=fgetc(f)) {
        /*here comes the beauty*/
        int in_section = 0;
        int out_of_section = 0;
        char name[7]; //longest one is driver
        if (c == '#' && in_section == 0) { //if we read a hashtag and in_section was false we enter into a section
            char * s_name = name;
            while (c != '\n') {
                *s_name = c;
                s_name += 1;
                c = getchar();
            }
            //if we are here we read the section name
            s_name == 0; //terminator for string of the title of section
            in_section = 1;
            /*do something */
        } else if (c == '#' && in_section == 1) { //we arrived to an end of section
            in_section = 0;
        } else if (in_section == 1) { //in this case we are inside the section
            if (name[0] == c) { //we are in a car section
                struct car * new_car = malloc(sizeof(struct car));
                while () //no time sorry, but would Itearte and the use strncpy
            } else if (name[0] == d){ //we are in a driver section
                struct driver * new_driver = malloc(sizeof(struct driver));
                while () //no time sorry, but would Itearte and the use strncpy
            } else if (name [0] == t) { //we are in a team section
                struct team * new_team = malloc(sizeof(struct team));
                while() //no time sorry, but would Itearte and the use strncpy
            }

        }
    }
    #endif
}


void racing_delete() {
    if (!Race) { //I assume that if the Race struct doesn't exists I return 1 becasue there is nothing to delete
        return 1;
    }
    while(Race->teams) { //I free the teams
        struct team * team = Race->teams->next_team;
        free(Race->teams->name) //I free the name of teh teams that are malloc objects
        free(Race->teams); //I free the team 
        Race->teams = team;
    }
    while (Race->cars) { //i free the cars
        struct car * carr = Race->cars->next_car;
        free(Race->cars->maker); //I free the make
        free(Race->cars->model); //I free the model
        free(Race->cars); //I free the car
        Race->cars = carr;
    }
    while (Race->drivers){ //i free the drivers
        struct driver * driverr = Race->driver->next_driver;
        free(Race->drivers->name);
        free(Race->driver);
        Race->driver = driverr;
    }
}

unsigned count_cars(const char *, const char *, const char *,const unsigned, const unsigned) {
    unsigned int count = 0;
    struct car * iter_car = Race->cars;
    while (iter_car) { //if car exists
        ++count;  //count it
        iter_car = iter->next_car; //point to next element of the linked list
    }
    return count;
}

unsigned count_drivers(const char *name , const char *team) {
    unsigned int count = 0;
    struct driver * iter_driver = Race->drivers;
    if(!name && !team) { //if both are null pointers
        struct driver * driv = Race->drivers;
        while (Race->drivers) {

        }
        return count;
    }
    if (name && !team) { //if only the name exists and team is a null pointer 
        struct driver * driv =  Race->drivers; 
        while (driv) { //we check for all drivers with this name
            if (strcmp(driv, name) == 0) { //if they are equal it returns 0
                ++count;
            }
            driv = driv->next_driver;
        }
        return count;
    }
    if (name && team) {
        int team_found = 0;
        struct team * found_team = Race->teams;
        while(found_team) {
            if(strcmp(found_team, team) == 0) {
                break
                team_found = 1
            }
        }
        if (team_found == 1) {
            struct driver * driv =  Race->; 
            while (driv) { //we check for all drivers with this name
                if (strcmp(driv, name) == 0) { //if they are equal it returns 0
                    ++count;
                }
                driv = driv->next_driver;
            }
            return count;
        } else {
            return 0; //failed
        }
    }
   

}
unsigned get_teams() {
    unsigned int count = 0;
    struct team * iter_team = Race->teams;
    while (Race->teams) { //if car exists
        ++count;  //count it
        iter_team = Race->teams->next_team; //point to next element of the linked list
    }
    return count;
}
