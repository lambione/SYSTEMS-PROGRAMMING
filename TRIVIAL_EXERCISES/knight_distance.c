#include<stdlib.h>
#include<stdio.h>

/*we wanna do bfs to find the knight moves*/
/*rember distance and previous (if we want to print the path) ARE IMPORTANTTTT*/
/*input is the position of the knight as the coordinates of rows and columns */

struct cell {
    unsigned int dist;
    struct cell * prev; //pointer to a cell
}

struct pos {
    int row;
    int col;
}

//I wanna iterate through all the adjecency positions by using vectors
struct pos knight_moves [] {
    {2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}
};


struct cell board[8][8]; //initialize the board as a bidamensional array 

int main(int argc, char * argv[]) { //argc is the input command and the name of the program is included in argc for example wc -w has 2 command arguments
    int r = 2, c = 1;
    if (argc > 1) {
        r = atoi (argv[1]);
    }
    if (argc > 2) {
        c = atoi (argv[2]);
    }

    struct pos Q[8*8]; //64 positions than 64
    struct pos * head = Q;
    struct pos * tail= Q;

    //initialization of the board
    for(int i = 0; i < 8; ++i) {
        for (int j = 0; j<8; ++j) {
            board[i][j].prev = 0; //0 is the null pointer 
        }
    }

    /*enque operation of r and c, enqueue(r,c)*/
    tail->row = r;
    tail->col = c;
    ++tail;

    board[r][c].dist = 0;
    board[r][c].prev = &(board[r][c]); //it is itself so address of board[r][c]

    while (tail != head) { /*while the queue is not empty*/
        //now we need to dequeue
        r = head->row;
        c = head->col;
        ++head;
        for (int i=0;i<8;++i) {
            int r2 = r + knight_moves[i].row;
            int c2 = c + knight_moves[i].col;
            if (r2>=0 && r2<8 && c2>= 0 && c2<8 && board[r2][c2].prev == 0) {
                tail->row = r2;
                tail->col = c2;
                ++tail;

                board[r2][c2].dist = board[r][c].dist + 1;
                board[r2][c2].prev = &(board[r][c]); 
            }
        }
    }

    for(int i = 0; i < 8; ++i) {
        for (int j = 0; j<8; ++j) {
            printf("%3d",board[i][j].dist);
        }
        printf("\n");
    }


}



