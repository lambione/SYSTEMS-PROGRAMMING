#include "blob.h"

unsigned int count_char (const struct blob * b, char c) {
    unsigned int counter = 0; 
    struct chunk_list * placeholder = b->sentinel.next;
    while(placeholder != &(b->sentinel)) {

        for(unsigned int i = 0; i<placeholder->c->length; ++i) {
            if (placeholder->c->data[i] == c) {
                ++counter;
            }
        }
        placeholder = placeholder->next;
    }
    return counter;
}

unsigned int copy_to_buffer (const struct blob * b, char * buf, unsigned int maxlen) {
    unsigned int counter = 0; 
    struct chunk_list * placeholder = b->sentinel.next;
    while(placeholder != &(b->sentinel)) {

        for(unsigned int i = 0; i<placeholder->c->length; ++i) {
            if(counter < maxlen) {
                // TA correction -> i is local to the loop, so we need to use counter
                buf[counter] = placeholder->c->data[i];
                ++counter;
            } else {
                return maxlen + 1;
            }
        }
        placeholder = placeholder->next;
    }
    return counter;

}
unsigned int copy_to_buffer_reverse (const struct blob * b, char * buf, unsigned int maxlen) {
    unsigned int counter = 0; 
    struct chunk_list * placeholder = b->sentinel.prev;
    while(placeholder != &(b->sentinel)) {

        // unsigned int counter = 0;  distraction made me create two couters BAD
        for(unsigned int i = placeholder->c->length; i>0; --i) {
            if(counter < maxlen) {
                // still i local to loop
                // do -1 in indexing, length is 1 more than access data 
                buf[counter] = placeholder->c->data[i-1];
                ++counter;
            } else {
                return maxlen + 1;
            }
        }
        placeholder = placeholder->prev;
    }
    return counter;

}