#include <string.h>
#include <cstdlib>

#include "messaging.h"

struct receiver {
    //server invokes this function to deliver messages
    char * interest; 
    void (*deliver)(struct receiver * r, const char * message);
};

struct server {
    char * message;
    struct receiver * receivers;
};

struct server * server_new() /* return 0 on failure */{
    struct server * s = (struct server *)malloc(sizeof(struct server));
    if (!s) return 0;
    s->message = 0;
}

void server_delete(struct server * s);


/* return 0 on failure */
int add_interest(struct server * srv, struct receiver * r, const char * interest) {
    char * i = (char *)malloc(strlen(interest) + 1);
    if (!i) return 0;
    strcpy(i,interest);
    r->interest = i;
}

void remove_interest(struct server * srv, struct receiver * r, const char * interest);

void clear_receiver(struct server * srv, struct receiver * r);

void clear_all(struct server * srv);

void send(const struct server * srv, const char * message);