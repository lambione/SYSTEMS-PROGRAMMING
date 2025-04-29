#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static struct teams {
    char name[21];
    unsigned int score;
    unsigned int gamePlayed;
    struct teams *  next;
} Team = {0,0,0,0};


void delete() {
    if(Team.next) {
        struct teams * m = Team.next;
        while (m) {
            if (m->name)
                free(m->name);
            struct teams * tmp = m;
            m = m->next;
            free(tmp);
        }
    }
}

int main (int argc, char * argv[]) {

    unsigned int max = 10;

    if (argc > 1 && argc < 3) {
        max = atoi(argv[1]);
    }

    // expected line is 45 long we can make it 46 for the 0
    char line[46];
    while(fgets(line,46,stdin)) {
        unsigned int scoreFirst;
        unsigned int scoreSecond;
        char teamFirst[21];
        char teamSecond[21];
        // now we are reading lines from stdin, now we need to look at the teams and see what to do 
        if(strlen(line) == 1) {
            continue;
        }
        char * token = strtok(line," ");
        // this counter will be useful to know at what point of the string we are in
        unsigned counter = 0;
        while (token != NULL) {
            ++counter;
            if (counter <= 4) {
                switch (counter) {
                    case 1 :
                        strcpy(teamFirst,token);
                        unsigned team_count = 0;
                        struct teams * iter = &Team;
                        while (iter) {
                            ++team_count;
                            if (strcmp(token,iter->name) == 0) {
                                goto skip;
                            }
                            if(iter->next == NULL) 
                                break;
                            iter = iter->next;
                        }
                        // if we are here we need to put a new team in 
                        if (team_count > max)  
                            return EXIT_FAILURE;

                        // if we are here we now need to add the new team to the linked list 
                        struct teams * new_T = malloc(sizeof(struct teams));
                        if (!new_T) return EXIT_FAILURE;
                        strcpy(new_T->name, token);
                        new_T->score = 0;
                        new_T->gamePlayed = 0; //played this one but we will think about it later
                        new_T->next = 0; //null ptr

                        iter->next = new_T;
                        skip :
                            break;
                    case 2 :
                        strcpy(teamSecond,token);
                        unsigned team_count2 = 0;
                        struct teams * iter2 = &Team;
                        while (iter2) {
                            ++team_count2;
                            if (strcmp(token,iter2->name) == 0) {
                                goto skip2;
                            }
                            if(iter2->next == NULL) 
                                break;
                            iter2 = iter2->next;
                        }
                        // if we are here we need to put a new team in 
                        if (team_count2 > max) 
                            return EXIT_FAILURE;

                        // if we are here we now need to add the new team to the linked list 
                        struct teams * new = malloc(sizeof(struct teams));
                        if (!new) return EXIT_FAILURE;
                        strcpy(new->name, token);
                        new->score = 0;
                        new->gamePlayed = 0; //played this one but we will think about it later
                        new->next = 0; //null ptr

                        iter2->next = new;
                        skip2 :
                            break;
                    case 3 :
                        scoreFirst = atoi(token);
                        break;
                    case 4 :
                        scoreSecond = atoi(token);
                        break;
                }
            }
            if (counter >= 4) {
                break;
            }
            token = strtok(NULL," ");
        }

        if (scoreFirst < scoreSecond) {
            struct teams * iterator = Team.next;
            while (iterator) {
                if (strcmp(teamSecond,iterator->name) == 0) {
                    iterator->score += 3;
                    iterator->gamePlayed += 1;
                } else if (strcmp(teamFirst,iterator->name) == 0)  {
                    iterator->gamePlayed += 1;
                }
                iterator = iterator->next;
            }
        } else if (scoreSecond < scoreFirst) {
            struct teams * iterator = Team.next;
            while (iterator) {
                if (strcmp(teamFirst,iterator->name) == 0) {
                    iterator->score += 3;
                    iterator->gamePlayed += 1;
                } else if (strcmp(teamSecond,iterator->name) == 0)  {
                    iterator->gamePlayed += 1;
                }
                iterator = iterator->next;
            }
        } else if (scoreSecond == scoreFirst) {
            struct teams * iterator = Team.next;
            while (iterator) {
                if (strcmp(teamFirst,iterator->name) == 0) {
                    iterator->score += 1;
                    iterator->gamePlayed += 1;
                } else if (strcmp(teamSecond,iterator->name) == 0)  {
                    iterator->score += 1;
                    iterator->gamePlayed += 1;
                }
                iterator = iterator->next;
            }
        }
    }


    // now we need to do something super brutto perche' dovremo iterare 837387438 volte sulla linked list

    // lotta contro me stesso facciamo un sort della nostra linked list al contrario dal piu grande al piu piccolo
    // era palesemente da fare con la doubly linked list fatto cosi;


    // ok sistemato ora &Team e' tipo la sentinel in una doubly linked list ma ho una single linked list 
    struct teams * previnitial = &Team;
    struct teams * prevfinal = Team.next;
    struct teams * tmpfinalprev = prevfinal;


    for(struct teams * lastIter = Team.next; lastIter; lastIter = lastIter->next) {
        struct teams * change = lastIter;
        for (struct teams * tmp = lastIter->next; tmp; tmp = tmp->next) {
            if (tmp->score > lastIter->score) {
                change = tmp;
                prevfinal = tmpfinalprev ;
            } 
            tmpfinalprev = tmp;
        }
        // compare addresses
        if(lastIter == change) 
            goto reset;
        struct teams * tempo = lastIter->next; //we need this apsolutely otherwise we loose the other linked list
        lastIter->next = change->next;
        previnitial->next = change;
        change->next = tempo;  
        prevfinal->next = lastIter;

        reset :
            // reset the initials
            previnitial = previnitial->next;
            prevfinal = previnitial->next;
            lastIter = change;
    }

    // now we've sorted the list by score but we need to pay attention to alphabetical order now, still a pain in the ass
    struct teams * initialprev = &Team;
    struct teams * finalprev = Team.next;
    struct teams * fptmp = finalprev;

    for(struct teams * Iter = Team.next; Iter; Iter = Iter->next) {
        struct teams * toChange = Iter;
        for (struct teams * tmp = Iter->next; tmp; tmp = tmp->next) {
            if (tmp->score == Iter->score) {
                if (strcmp(tmp->name,toChange->name) ==  -1) {
                    /*do something*/
                    toChange = tmp;
                    finalprev = fptmp;
                }
                fptmp = tmp;
            } else {
                // if they are different we break
                break;
            }
        }
        // compare addresses
        if(Iter == toChange) 
            goto setnew;
        struct teams * tempo = Iter->next; //we need this apsolutely otherwise we loose the other linked list
        Iter->next = toChange->next;
        initialprev->next = toChange;
        toChange->next = tempo;  
        finalprev->next = Iter;

        setnew :
            // reset the initials
            initialprev = initialprev->next;
            finalprev = initialprev->next;
            Iter = toChange;
    }

    // lets print
    struct teams * iterator = Team.next;
    while (iterator) {
        printf("%s %d %d\n",iterator->name,iterator->score, iterator->gamePlayed);
        iterator = iterator->next;
    }
    
    return EXIT_SUCCESS;
        
}
