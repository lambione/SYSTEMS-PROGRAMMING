#include<stdio.h>
#include<stdlib.h>





struct bufile {
    char * begin;
    char * end;
};

struct bufile * bufopen(char * begin, char * end) {
    struct bufile * buf = malloc(sizeof(struct bufile));
    if (buf) {
        buf->begin = begin;
        buf->end = end;
    }
    return buf; 
}

//size = end-begin

void bufclose(struct bufile * buf) {
    free(buf);
}

char *bufgets(char *s, int size, struct bufile * buf) {

    #if 0
    //reads from buf and stiores it in s
    if(buf->begin == buf->end) {
        return 0;
    }
    int len = 0;
    while(buf->begin != buf->end && len < size-1 ) {
        if(*(buf->begin) == '\n') {
            s[len] = *(buf->begin);
            break;
        }
        s[len] = *(buf->begin);
        ++(buf->begin);
        ++len;
    }
    if (s[len] == '\n')
        s[len +1] = 0;
    if (len == size-1) {
        s[len] = 0;
    } else {
        s[len +1] =0;
    }
    return s;   
    #endif

    #if 1
    //carza implementation
    int i;
    if (buf->begin == buf->end)
	    return 0;
    for (i = 0; i < size - 1; ++i) {
	    s[i] = *(buf->begin);
	    buf->begin += 1;
        if (s[i] == '\n' || buf->begin == buf->end) {
            s[i + 1] = 0;
            return s;
        }
    }
    s[i] = 0;
    return s;
    #endif
}