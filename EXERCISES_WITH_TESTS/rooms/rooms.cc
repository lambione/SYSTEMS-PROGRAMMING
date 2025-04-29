#include <stdio.h>

#include "rooms.h"

struct room {
    int floor;
    int number;
    int capacity;
    struct schedule * events;
    struct room * next;
};

const int ANY_FLOOR = -1;
const int ANY_ROOM_NUMBER = -1;
const int ANY_CAPACITY = -1;

struct schedule {
    char * event;
    int start;
    int finish;
    int duration;
    struct schedule * next;
};


void clear();

void add_rooms(const room * begin, const room * end) {

}

//r capacity is the minimum capacity for the room
//if r->capacity is equal to any capacity, the any capacity is good
//similarly for the floor 
//similarly for room number
int make_reservation(room * r, schedule * t, const char * event) {
    
}

int cancel_reservation(int floor, int number, int start) {

}

//print on the standard output
void print_schedule(int floor, int number, int start, int finish);