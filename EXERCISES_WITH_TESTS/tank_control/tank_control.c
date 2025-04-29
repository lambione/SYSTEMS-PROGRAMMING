#include<stdio.h>
#include<stdlib.h>



unsigned int tank_cap = 1000000;
unsigned int bottle = 750;
unsigned int waste = 0; //initially 0
unsigned int tank = 0; //initally 0


void clear() { //resets tank level and waster counter to 0
    waste = 0;
    tank = 0;
}



void change_bottle_capacity(unsigned int c) { //can change dynamically with this, (the bottole capacity)
    bottle = c;
}


void change_tank(unsigned int c) { //changes tank ith a new one of capcacity c
    if(tank > c) {
        waste = waste + (tank -c); //c is smaller than tank so it is filled 
        tank = c;
    }
    tank_cap = c;
}

void add(unsigned int c) { //adds c milliliters of liquid arrived from prodeucer

    if(c > tank_cap - tank) {
        waste = waste + (c -(tank_cap-tank));
        tank = tank_cap;
    } else {
        tank = tank + c;
    }

#if 0
    for(unsigned int i=0; i<c; i++) {
        if(tank<=tank_cap) {
            ++tank;
        } else {
            ++waste;
        }
    }
#endif
} 

unsigned int ship_out_bottles() { //called to prepare biottoles for shipping, returns a number that will be the maximum number of bottles to fill

    unsigned int b = tank / bottle;
    tank = tank % bottle;
    return b;

//also this one is good but carza opvviamente does it better

#if 0
    unsigned int shipped = 0;
    while (tank - bottle >= 0 ) {
        ++shipped;
        tank = tank-bottle;
    }
    return shipped;

#endif
} 

unsigned int get_wastes() { //returns the total amout of liquid discarded 
    return waste;
} 

unsigned int get_tank_level() { //returns the current amout of liquid
    return tank; //we return the stackpointer - the initial 
} 







#if 0 
//tank has capacity 1000000ml

int *tank = malloc(1000000 * sizeof(int)); //we create an object that can store 1000000 mlliters
int *sp_tank = tank; //we put a stackpointer that initially points to the beginning of the tank since it is empty

unsigned int waste = 0;

//all capacities values are in milliliters

//bottles have capacities 750 ml

int *bottle = malloc(750 * sizeof(int));
int *sp_bottle = bottle; //we place a stackpointer also for the bottle 


void clear() { //resets tank level and waster counter to 0

    while(sp_tank != tank) { //we pop all elements from the stack
        --sp_tank;
    }
    waste = 0; //reset waste counter 

}



void change_bottle_capacity(unsigned int c) { //can change dynamically with this, (the bottole capacity)
    bottle = realloc(bottle, c*sizeof(int));
}


void change_tank(unsigned int c) { //changes tank ith a new one of capcacity c
    tank = realloc(tank, c*sizeof(int)); 
}

void add(unsigned int c) { //adds c milliliters of liquid arrived from prodeucer

    unsigned int wasted = c;

    while(sp_tank  && wasted > 0) {
        *sp_tank = 1;
        ++sp_tank;
        --wasted;
    }
    
    waste = wasted + waste;  
} 

unsigned int ship_out_bottles() { //called to prepare biottoles for shipping, returns a number that will be the maximum number of bottles to fill

    int shipped = 0;

    while(sp_tank != tank) {
        if (!sp_bottle) { //if we filled a bottle 
            ++shipped;
            sp_bottle = bottle;
        }
        *sp_bottle = 1; //fill the first ml in bottle
        ++sp_bottle; //go to possible next one 
        --sp_tank; //take away ml from real tank
    }


    free(tank);
    free(bottle);
    return shipped;


} 

unsigned int get_wastes() {

    return waste;

} //returns the total amout of liquid discarded 

unsigned int get_tank_level() { //returns the current amout of liquid
    return sp_tank - tank; //we return the stackpointer - the initial 
} 

#endif
