#include <string.h>
#include <stdlib.h>
#include <string.h>

#include "media_stats.h"

struct views {
    char * user;
    double start;
    double finish;
    unsigned multiple; //needed for unique users
    struct views * next;
};

struct media {
    char * title;
    double d_time; //in seconds
    struct views * w;
    struct media * next;
};

static struct database {
    struct media * medias;
} M = {0};


// Add a video or music title with the given total duration. Return 1
// or 0 on success or failure, respectively.
int add_media(const char * title, double duration) {
    char * t = (char *)malloc(strlen(title)+1);
    if (!t) {
        return 0;
    }
    strcpy(t, title);
    
    struct media * m = (struct media *)malloc(sizeof(struct media));
    if (!m) {
        free(t);
        return 0;
    }
    m->title = t;
    if (duration < 0.0) {
        return 0;
    }
    m->d_time = duration;
    m->w = 0;
    m->next = 0;

    struct media * iter = M.medias;
    while (iter) {
        if (strcmp(iter->title, title) == 0) 
            return 0; 
        iter = iter->next;
    }
    
    if(!M.medias) {
        M.medias = m;
        return 1;
    }

    //we add it at the beginning otherwhise
    iter = M.medias;
    M.medias = m;
    m->next = iter;
    return 1;
}

// Add a media viewing of the given title by the given user of a
// segment defined by the given start and finish times. Return 1 or 0
// on success or failure, respectively.
int add_view(const char * title, const char * user, double start, double finish) {
    
    // we need to assume that the user exists

    struct media * iter = M.medias;
    while (iter) {
        if (strcmp(iter->title, title) == 0) {
            if (start > 0 && finish < iter->d_time) {
                struct views * vv = (struct views *)malloc(sizeof(struct views));
                if (!vv) {
                    return 0;
                }
                char * usr = (char *)malloc(strlen(user) + 1);
                strcpy(usr, user);
                vv->user = usr;
                vv->start = start;
                vv->finish = finish;
                vv->next = 0;

                if(iter->w) {
                    struct views * tmp = iter->w;
                    iter->w = vv;
                    vv->next = tmp;
                } else {
                    iter->w = vv;
                }
                return 1;  
            } else {
                return 0;
            }
        }
    }
    return 0;

}
// Clear all media titles and therefore all views.
void clear_media() {

    struct media * mm = M.medias;

    while(mm) {
        free(mm->title);
        while(mm->w) {
            free(mm->w->user);
            struct views * tmp = mm->w;
            mm->w = mm->w->next;
            free(tmp);
        }
        struct media * tmp = mm;
        mm = mm->next;
        free(tmp);
    }

}
// Clear all media views but keep the media titles.
void clear_views() {

    struct media * mm = M.medias;

    while(mm) {
        while(mm->w) {
            free(mm->w->user);
            struct views * tmp = mm->w;
            mm->w = mm->w->next;
            free(tmp);
        }
        mm = mm->next;
    }
}
// Number of unique users who have viewed any portion of the given
// media. Return -1 if the title does not exist.
int unique_viewers(const char * title) {

    unsigned counter = 0;
    struct media * iter = M.medias;
    while (iter) {
        if (strcmp(iter->title, title) == 0) {
            struct views * v = iter->w;
            while (v) {
                if (v->multiple == 0) {
                    ++counter;
                    v->multiple = 1;
                } else if (v->multiple == 1) {
                    continue;
                }
                struct views * vv = v;
                while(vv){
                    if (strcmp(vv->user,v->user) == 0)  {
                        vv->multiple = 1;
                    }
                    vv = vv->next;
                }
                v = v->next;
            }
            // replace all views multiple to 0
            struct views * lastIter = iter->w;
            while (lastIter) {
                lastIter->multiple = 0;
                lastIter = lastIter->next;
            }

            return counter;
        }
        iter = iter->next;
    }
    return -1;

}
// Total time of the given title that the given user has seen at least
// once. Return -1 if the title does not exist. Return 0 if the user
// does not exist.
double total_time_viewed(const char * title, const char * user) {
    unsigned int lower_bound = 0;
    unsigned int upper_bound = 0; 

    struct media * iter = M.medias;
    while (iter) {
        if (strcmp(iter->title, title) == 0) {

            // now we put in the lower bound the max time and in the upper bound we leave 0
            lower_bound = iter->d_time;

            // I place multiple to 1 to all users
            struct views * vv = iter->w;
            while(vv){
                if (strcmp(vv->user,user) == 0)  {
                    vv->multiple = 1;
                }
                vv = vv->next;
            }

            struct views * iter_v = iter->w;
            while(iter_v){
                if (iter_v->multiple == 1)  {
                    if (lower_bound > iter_v->start)
                        lower_bound = iter_v->start;
                    if (upper_bound < iter_v->finish)
                        upper_bound = iter_v->finish;
                }
                iter_v = iter_v->next;
            }

            // replace all views multiple to 0
            struct views * lastIter = iter->w;
            while (lastIter) {
                lastIter->multiple = 0;
                lastIter = lastIter->next;
            }

            return upper_bound-lower_bound;
        }
        iter = iter->next;
    }
    return -1;


}
// Number of users who viewed the entire duration of the given media
// file in one or more viewings. Return -1 if the title does not exist.
int complete_views(const char * title) {
    unsigned int lower_bound = 0;
    unsigned int upper_bound = 0; 

    unsigned counter = 0;
    struct media * iter = M.medias;
    while (iter) {
        if (strcmp(iter->title, title) == 0) {

            // now we put in the lower bound the max time and in the upper bound we leave 0
            lower_bound = iter->d_time;

            struct views * v = iter->w;
            while (v) {
                if (v->multiple == 0) {
                    v->multiple = 1;
                } else if (v->multiple == 1) {
                    continue;
                }
                struct views * vv = v;
                while(vv){
                    if (strcmp(vv->user,v->user) == 0)  {
                        vv->multiple = 1;
                    }
                    vv = vv->next;
                }
                // I iterate over people with multiple setted to 1
                struct views * iter_v = iter->w;
                while(iter_v){
                    if (iter_v->multiple == 1 && strcmp(v->user,iter_v->user) == 0)  {
                        if (lower_bound > iter_v->start)
                            lower_bound = iter_v->start;
                        if (upper_bound < iter_v->finish)
                            upper_bound = iter_v->finish;
                    }
                    iter_v = iter_v->next;
                }

                if ((upper_bound - lower_bound) == iter->d_time) 
                    ++counter;

                lower_bound = iter->d_time;
                upper_bound = 0;

            }

            // replace all views multiple to 0
            struct views * lastIter = iter->w;
            while (lastIter) {
                lastIter->multiple = 0;
                lastIter = lastIter->next;
            }

            return counter;
        }
        iter = iter->next;
    }
    return -1;
}