#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <time.h>
// #include <check.h>
//////////////////////////// Testing Platform for all in-game logic functionality
/* MACROS */
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
/* Minesweeper grid dimensions */
#define X_GRID 3
#define Y_GRID 3



/* Circle Struct */
struct circleObj{
  int x_a;
  int y_a;
  bool isMoving;
};
typedef struct circleObj Circle;


/* Grid Struct */
struct space {
  bool holdsMine;
  int adjacentNeighbours; //if ¬holdsMine, should have a particular value representing how many neighbours have mines
  int x_pos, y_pos;
};
typedef struct space Space;



/* GAME LOGIC */
void assignMine(Space * grid){
  int rand_num;
  srand((unsigned) time(NULL));
  int mine_count = 0;
  for(int m = 0; m< (X_GRID * Y_GRID); m++){
    rand_num = rand() % 20;
    if(rand_num >= 16){
      grid[m].holdsMine = true;
    }
    else{
      grid[m].holdsMine = false;
    }
  }
}

/* kek is this 5-point stencil ?????*/
void identifyNeighbours(Space * grid){
  int traversalIndex = 0;

  //inner square
  for(int M = (X_GRID+1) ; M < ( (X_GRID-1) * (Y_GRID-1) ); M++) {
    traversalIndex = M % Y_GRID;

    //checks if pointing at top or bottom row value
    if( (traversalIndex != 0) && (traversalIndex != (Y_GRID-1)) ) {
      grid[M].adjacentNeighbours = 0;
      grid[M].adjacentNeighbours += grid[M-1].holdsMine + grid[M+1].holdsMine + grid[ (M + X_GRID) ].holdsMine
                                 + grid[  (M - X_GRID) ].holdsMine + grid[ (M-1) + X_GRID ].holdsMine
                                 + grid[ (M-1) - X_GRID ].holdsMine + grid[ (M+1) + X_GRID ].holdsMine
                                 + grid[ (M+1) - X_GRID ].holdsMine;
    }
  }
  //four corners

  //top & bottom rows

  //left & right columns
}


void regionLock(Circle c){
  int x_shift, y_shift;
  for(int ii = 0; ii < X_GRID; ii++ ){
    x_shift = 25 * ii;
    for(int jj = 0; jj < Y_GRID; jj++){
      y_shift = 25* jj;
      if(( (97 + x_shift) < c.x_a && c.x_a < (107 + x_shift) ) && ( (43+y_shift) < c.y_a && c.y_a < (53+y_shift) )) {c.isMoving=false;}
    }
  }
}

/* Unit Testing */




/* EXECUTION */
int main(int argc, char const *argv[]) {
  Space grid[X_GRID * Y_GRID];
  return 0;
}
