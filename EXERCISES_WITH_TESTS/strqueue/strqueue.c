#include"strqueue.h"

char * Memory = 0;
size_t size = 0;
char * head = 0;
char * tail = 0;

void strqueue_use_buffer(char * mem, size_t mem_size) {
    Memory = mem;
    size = mem_size;
    head = mem;
    tail = mem;
}

void strqueue_clear() {
    head = Memory;
    tail = Memory;
}

int strqueue_enqueue(const char * s) {
    //compute length of the string
    unsigned int length = 0;
    while (s[length] != 0) {
        ++length;
    }

    if ((tail-head) + length+1 >= size) {
        return 0;
    } 
    if ((tail-Memory) + (length+1) >= size) {
        char * p;   
        p = Memory;

        while(head != tail) {
            *p = *head;
            ++head;
            ++p;

        }
        tail = p;
        head = Memory;
    }
    //now write the string
    for (int i=0; i<length; ++i) {
        *tail = *s;
        ++tail;
        ++s;
    }
    *tail = 0;
    ++tail;
    return 1;
}

const char * strqueue_dequeue() {
    if (head == tail) {
        return 0;
    } else {
        char * t;
        t = head;

        while (*head != 0) {
            ++head;
        }
        ++head;
        return t;
    }
}