/*we want to represewnt a point in a 2d space*/

float a[2]

struct {   /*variable declaration, object declaration*/
    float x;
    float y;
} p;

struct point {    /*this is a type declaration*/
    float x;        /*the type is 'struct point'*/
    float y;
}

struct point r; /*declaration and definition of an object of type struct point*/

struct point q = {3.0,2.0};
struct point q2 = {.x = 3.0, .y = 2.0};

int A [10] = {1,2,3,4,5,6,7,8,9,10};

int B[] = {1,2,7,8};

struct  point T[3] = {{0,0}, {4,0}, {0,3}};

struct triangle {
    /*or just do an array struct point P[3]*/
    /*char name[11] we can place something different also in a struct*/
    struct point A;
    struct point B;
    struct point C;
}

struct triangle T;
struct triangle *p = &T;

float * fp = (float *)p;



// int main() {
//     struct triangle t;
//     (t.p[0]).x = 5.0;  /*object of type struct point is the one in the parent and we acces "field" x*/
//     (t.p[0]).y = 7.0; 
//     // printf ("A: (%f,%f)\n")
// }


struct person {
    char * name;
    struct person *mama;
    struct person * papa;
}


int main() {
    struct person * p;
    printf ("%s's mama is %s\n", (*p).name, (*(*p).mama).name); /*cumbersomeeee as fuckkkk*/
    printf ("%s's mama is %s\n", p->name, p->mama->name); /*sooo juicyyyy betterrrrrrrrr*/
}

// this is baddddd use the code up here
typedef struct {
    float x;
    float y;
} point2d;  /*now point2d is a fuxkiiingg type*/

point2d s;


