#include <stdlib.h>
#include <stdio.h>
#include "processes.h"

//process itself
struct process {
	unsigned int process_id;
	unsigned int parent_id;
	char user[9];
	unsigned int priority;
	float cpu_usage;
	unsigned long resident_size;
	unsigned long size;
	unsigned long virtual_size;
	char command[16];
	struct process * next;
};

//list of processes
struct processes {
	struct process * pr;
};

static struct processes * db = 0;

struct processes * new_processes() {
	db = (struct processes *)malloc(sizeof(struct processes));
	if (!db) return db;
	db->pr = 0;
	return db;
}

void delete(struct processes * p) {
	while(p->pr) {
		struct process * tmp = p->pr;
		p->pr = p->pr->next;
		free(tmp);
	}
	free(p);
}

int add_from_file(struct processes * p, const char * filename) {
	FILE * f = fopen(filename, "r");
	if (!f) return 0;

	struct process * pp = malloc(sizeof(struct process));
	struct process * iter = p->pr;
	if (!pp) return 0;
	while(fscanf(f, "%u %u %8s %u %f %ld %ld %ld %15s",
		&(pp->process_id), 
		&(pp->parent_id), 
		pp->user,
		&(pp->priority),
		&(pp->cpu_usage),
		&(pp->resident_size),
		&(pp->size), 
		&(pp->virtual_size),
		pp->command) == 9) 
		{
			pp->user[8] = 0;
			pp->command[15] = 0;
			pp->next = 0;
			if (!iter) {
				p->pr = pp;
				iter = p->pr;
			} else {
				iter->next = pp;
				iter = iter->next;
			}
	}
	return 1;
}
extern void clear(struct processes * p) {
	while(p->pr) {
		struct process * tmp = p->pr;
		p->pr = p->pr->next;
		free(tmp);
	}
}

struct query {
	int priority;
	long int rss;
	long int size;
	long int vsize;
	float cpu_usage;
};

struct query_result {
	struct process * proc;
}


struct query_result * search(struct processes * p, const struct query * q) {

	struct query_result * result= malloc(sizeof(struct query_result));
	if (!result) return result;
	result->proc = 0;
	result->next = 0;

	struct process * tmp = result->proc;

	struct process * iterator = p->pr;
	while(iterator) {

		if (q->cpu_usage < 0)
			q->cpu_usage = q->cpu_usage * -1 
		if ((q->priority == 0 || (q->priority == iterator->priority)) &&
			(q->rss == 0 || (q->rss == iterator->resident_size)) &&
			(q->size == 0 || (q->size == iterator->size)) && 
			(q->vsize == 0 || (q->vsize == iterator->virtual_size)) && 
			(q->cpu_usage == 0 || (q->cpu_usage == iterator->cpu_usage))) {
				result->
			}
	}
}
int get_pid(struct query_result *r);
int get_ppid(struct query_result *r);
const char * get_user(struct query_result *r);
int get_priority(struct query_result *r);
float get_cpu_usage(struct query_result *r);
long int get_rss(struct query_result *r);
long int get_size(struct query_result *r);
long int get_vsize(struct query_result *r);
const char * get_command(struct query_result *r);
struct query_result * next(struct query_result *);
void terminate_query(struct query_result *);