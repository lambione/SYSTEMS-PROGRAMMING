#include<assert.h>
#include<stdlib.h>

//we are gonna use a STATIC interface which means we r gonna have just 1 stack
//implemented as a linked list
int push(int x);
int pop();
void clear();
int is_empty();
/*linked list from the top to the bottom*/

/*declaration of a type*/
struct stack_elem {
    int value;
    struct stack_elem * next;
}

struct stack_elem * S = NULL;

/*stack of int*/
int push(int x) { /*returns success failure*/
    struct stack_elem * new_elem = malloc(sizeof(struct stack_elem)); //this creates the object
    if (!new_elem) {
        return 0;
    }
    new_elem->value = x; 
    new_elem->next = S;
    S = new_elem;
    return 1;

}

int pop(){ /*return element,or aborts*/
    assert (S != NULL); //abort
    int result = S->value; //store the value
    struct stack_elem * tmp = S; //store pointer
    S = S->next;
    free(tmp);
    return result;
}

void clear() {
    while (S) { //while S is a valid pointer
        struct stack_elem * tmp = S; //store pointer
        S = S->next;
        free(tmp);
    }
}

int is_empty() {
    return (S == NULL);
}

int main() {
    assert (is_empty());

    push(7);
    assert (!is_empty());

    assert (pop() == 7);
    assert (is_empty());

    for(int i = 0; i<100, ++i) {
        assert(push(i+38));
    }
    assert(push(200000000));
    clear();
    assert (is_empty());
    assert(push(1));
    assert(push(2));
    assert(push(4));
    assert(pop() == 4);
    //....

}

