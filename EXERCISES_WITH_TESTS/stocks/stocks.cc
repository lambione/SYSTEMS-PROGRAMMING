#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "stocks.h"

struct trade {
    char company_name[6]; 
    unsigned int quantity; //stocks that are traded 
    double price;
    double trade_time; //representing seconds from a fixed date
    struct trade * next;
};

struct trades_log {
    double time_window;
    struct trade * trades;
};

// time window is 60 seconds by default

struct trades_log * new_log(){
    struct trades_log * log = (struct trades_log * )malloc(sizeof(struct trades_log));
    if (!log) {
        return log; //return null pointer
    }
    log->time_window = 0;
    log->trades = 0;
    return log;
} 

void delete_log(struct trades_log * l) {
    struct trade * iterator = l->trades;
    while (iterator) {
        struct trade * tmp = iterator;
        iterator = iterator->next;
        free(tmp);
    }
    free(l);
}

// new trade made at time t for quantity q of stock s at price p can be added to a log l
// quantity and price must be positive to be valid 
// time is not less than the time of any of the previous trade
// return 1 on success and 0 on failure 
int new_trade(struct trades_log * l, double time, const char * symbol, double price, unsigned int quantity) {
    struct trade * new_trade = (struct trade *)malloc(sizeof(struct trade));
    if (!new_trade) return 0;
    strcpy(new_trade->company_name,symbol);
    if (price < 0 || quantity < 0) {
        free(new_trade);
        return 0;
    }

    new_trade->quantity = quantity;
    new_trade->price = price;

    
    struct trade * iter = l->trades;
    if(iter) {
    double t_time = l->trades->trade_time;
        while(iter) {
            if(iter->trade_time > t_time)
                t_time = iter->trade_time;
            if(!iter->next) {
                break;
            }
            iter = iter->next;
        }
        if (time < t_time) {
            free(new_trade);
            return 0;
        }
    }

    new_trade->trade_time = time;
    new_trade->next = 0;
    if(iter) {
        iter->next = new_trade;
    } else {
        l->trades = new_trade;
    }

    set_time_window(l,l->time_window);
    return 1;

}


void clear(struct trades_log * l) {
    struct trade * iterator = l->trades;
    while (iterator) {
        struct trade * tmp = iterator;
        iterator = iterator->next;
        free(tmp);
    }
}

// log of trades for set time windows, when this function reduces the window we need to remove times that fall out
void set_time_window(struct trades_log * l, double w) {
    if (w <= l->time_window) {
        /*delete from log the outer */
        struct trade * iterator = l->trades;
        if (!iterator) {
            l->time_window = w;
            return;
        }
        while(iterator) {
            if (!iterator->next) {
                break;
            }
            iterator = iterator->next;
        }
        double threshold = iterator->trade_time - w;
        struct trade * iter = l->trades->next;
        if(!iter) return;
        struct trade * prev = l->trades;
        while(iter) {
            if(iter->trade_time < threshold) {
                prev->next = iter->next;
                struct trade * tmp = iter;
                iter = iter->next;
                free(tmp);
            } else {
                iter = iter->next;
            }
            prev = prev->next;
        }

        // then change the time
        l->time_window = w;
    } else {
        // otherwise just change the time window
        l->time_window = w;
    }

}

unsigned int total_quantity(const struct trades_log * l) {
    struct trade * iter = l->trades;
    if (!iter) return 0;
    unsigned counter = 0;
    while(iter) {
        counter += iter->quantity;
        iter = iter->next;
    }
    return counter;
}

double high_price(const struct trades_log * l) {
    struct trade * iter = l->trades;
    if (!iter) return 0;
    unsigned max = 0;
    while(iter) {
        if(max < iter->price)
            max = iter->price;
        iter = iter->next;
    }
    return max;
}

double low_price(const struct trades_log * l) {
    struct trade * iter = l->trades;
    if (!iter) return 0;
    double min = high_price(l);
    while(iter) {
        if(min > iter->price)
            min = iter->price;
        iter = iter->next;
    }
    return min;
}

double stock_high_price(const struct trades_log * l, const char * symbol) {
    struct trade * iter = l->trades;
    if(!iter) return 0;
    double max = 0;
    while(iter) {
        if (strcmp(symbol,iter->company_name) == 0) {
            if(max < iter->price)
                max = iter->price;
        }
        iter = iter->next;
    }
    return max;
}

double stock_low_price(const struct trades_log * l, const char * symbol) {
    struct trade * iter = l->trades;
    if(!iter) return 0;
    double min = stock_high_price(l,symbol);
    while(iter) {
        if (strcmp(symbol,iter->company_name) == 0) {
            if(min > iter->price)
                min = iter->price;
        }
        iter = iter->next;
    }
    return min;
}

double stock_avg_price(const struct trades_log * l, const char * symbol) {
    struct trade * iter = l->trades;
    if (!iter) return 0;
    double sum = 0;
    unsigned int counter = 0;
    while(iter) {
        if (strcmp(symbol,iter->company_name) == 0) {
            ++counter;
            sum += iter->price;
        }
        iter = iter->next;
    }
    if(sum == 0) return 0;
    return sum / counter;
}