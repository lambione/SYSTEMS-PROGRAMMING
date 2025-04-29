#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#include "videos.h"


struct platform{
    struct video * videos; //points to the list of videos
    int counter_videos;  //number of actual videos inside
    // struct platform *next_platform; //did it but useless
};

struct video {
    char Title[101];
    unsigned int duration; //duration
    unsigned int id; //must be given from us
    unsigned int view; //if it is greater or equal to duration, the is a full_view
    unsigned int full_views;
    struct video * next;
};

struct platform * create () {
    struct platform * new_platform = malloc(sizeof(struct platform));
    if(new_platform) {
        new_platform->counter_videos = 0;
        new_platform->videos = 0; //the null pointer
    }
    return new_platform; 
}

void destroy (struct platform * p) {
    clear(p); //first deallocate all lined list
    free(p); //then deallocate platform itself
}

void clear (struct platform * p) {
    while(p->videos) {
        struct video * tmp = p->videos->next;
        //no need to free the title, OS takes care of that 
        free(p->videos);
        p->videos = tmp;
    }
}


int add_video (struct platform * p, const char * title, int duration) {
    //initilaize a struct
    struct video * new_vid = malloc(sizeof(struct video));
    if(!new_vid) return -1;
    //update the video_counter that is also used to generate id's of our videos
    ++p->counter_videos;
    //copy the title in our structure
    strcpy(new_vid->Title,title);
    //put duration to our video
    new_vid->duration = duration; //put minuets
    //initilaize the full views
    new_vid->full_views = 0;
    //give a unique id
    new_vid->id = p->counter_videos; 
    //link the element to the list
    new_vid->next = p->videos;
    p->videos = new_vid;
    //return the identifier
    return new_vid->id; 
}


int add_view (struct platform * p, int video_id, int minutes) {

    for(struct video * vid = p->videos; vid; vid = vid->next) {
        if (vid->id == video_id) {
            //we do this just for the returning the total viewings
            vid->view += minutes;
            //we check just in this occasion if the duration given is greater than the actual duration we add a full_view
            if (vid->duration <= minutes) {
                ++vid->full_views;
            }   
            return 1;
        }
    }
    return 0;
}

int total_view_minutes(struct platform * p) {
    int total = 0;
    for(struct video * vid = p->videos; vid; vid = vid->next) 
        total += vid->view;    
    return total; 
}

int total_full_views (struct platform * p) {
    int total_full = 0;
    for(struct video * vid = p->videos; vid; vid = vid->next) 
        total_full += vid->full_views; 
    return total_full;
}

int video_by_title (struct platform * p, const char * title) {

    for(struct video * vid = p->videos; vid; vid = vid->next) {
        if (strcmp(vid->Title,title) == 0) {
            return vid->id;
        }
    }
    return -1;
}
