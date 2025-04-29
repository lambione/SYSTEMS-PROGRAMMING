#include <stdlib.h>
#include <stdio.h>

struct assistant {
#define MAX_NAME_LEN 50

    char name[MAX_NAME_LEN];
    int fall_avail;
    int spring_avail;
    struct assistant * next;
};

struct course {
#define MAX_TITLE_LEN 200

    char title[MAX_TITLE_LEN];
    char semester;
    int required_ta;
    struct course * next;
};

struct course * courses = 0;
struct assistant * assistants = 0;

static int read_courses(const char * fname) {
    FILE * f;
    
    if ((f = fopen(fname, "r")) == 0) {
	fprintf(stderr, "could not open courses file %s\n", fname);
	return 0;
    }

#define MAX_LINE_LEN 2

    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, f)) {
	struct course * new_c = malloc(sizeof(struct course));
	if (!new_c) {
	    fprintf(stderr, "could not allocate memory for course\n");
	    fclose(f);
	    return 0;
	}
	new_c->next = courses;
	courses = new_c;

	int i;
	for(i = 0; i < MAX_TITLE_LEN && line[i] != ','; ++i)
	    new_c->title[i] = line[i];
	if (line[i] != ',') {
	    fprintf(stderr, "bad format in courses file:\n%s\n", line);
	    fclose(f);
	    return 0;
	}
	new_c->semester = line[++i];
	++i;
	if (sscanf(line + i, ",%d", &(new_c->required_ta)) < 1) {
	    fprintf(stderr, "bad format in courses file:\n%s\n", line);
	    fclose(f);
	    return 0;
	}
    }
    fclose(f);
    return 1;
}

static int read_assistants(const char * fname) {
    FILE * f;
    
    if ((f = fopen(fname, "r")) == 0) {
	fprintf(stderr, "could not open assistants file %s\n", fname);
	return 0;
    }

    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, f)) {
	struct assistant * new_a = malloc(sizeof(struct assistant));
	if (!new_a) {
	    fprintf(stderr, "could not allocate memory for assistant\n");
	    fclose(f);
	    return 0;
	}
	new_a->next = assistants;
	assistants = new_a;

	int i;
	for(i = 0; i < MAX_NAME_LEN && line[i] != ','; ++i)
	    new_a->name[i] = line[i];
	if (sscanf(line + i, ",%d,%d", &(new_a->fall_avail), &(new_a->spring_avail)) < 2) {
	    fprintf(stderr, "bad format in assistants file:\n%s\n", line);
	    fclose(f);
	    return 0;
	}
    }
    fclose(f);
    return 1;
}

void clear_all() {
    while (assistants) {
	struct assistant * a = assistants;
	assistants = assistants->next;
	free(a);
    }

    while (courses) {
	struct course * c = courses;
	courses = courses->next;
	free(c);
    }
    return;
}

static void assign_assistants(int n, char semester) {
    if (n > 0) {
	for (struct assistant * a = assistants; a != 0; a = a->next) {
	    switch(semester) {
	    case 'F':
		if (a->fall_avail > 0) {
		    a->fall_avail -= 1;
		    printf("%s ", a->name);
		    n -= 1;
		    if (n == 0) {
			printf("\n");
			return;
		    }
		}
		break;
	    case 'S':
		if (a->spring_avail > 0) {
		    a->spring_avail -= 1;
		    printf("%s ", a->name);
		    n -= 1;
		    if (n == 0) {
			printf("\n");
			return;
		    }
		}
		break;
	    default:
		fprintf(stderr, "bad semester: %c\n", semester);
		return;
	    }
	}
	printf("(INCOMPLETE)\n");
    }
}

int main(int argc, char * argv[]) {
    if (argc < 3) {
	fprintf(stderr, "usage: %s <courses-file> <people-file>\n", argv[0]);
	return 1;
    }

    if (!read_courses(argv[1]) || !read_assistants(argv[2])) {
	clear_all();
	return 1;
    }

    for (const struct course * c = courses; c != 0; c = c->next) {
	printf("%s\n", c->title);
	assign_assistants(c->required_ta, c->semester);
	printf("\n");
    }
    clear_all();
    return 0;
}