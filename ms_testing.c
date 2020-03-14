#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
// #include <check.h>
//////////////////////////// Testing Platform for all in-game logic functionality
/* MACROS */
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
/* Minesweeper grid dimensions */
#define X_GRID 5
#define Y_GRID 5



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
int identifyNeighbours(Space * grid, int index){
  int traversalIndex = 0;
  int neighbourCount = 0;

  //inner square
  for(int M = (X_GRID+1) ; M < ( (X_GRID) * (Y_GRID) ); M++) {
    traversalIndex = M % Y_GRID;

    //checks if pointing at top or bottom row value
    if( ((traversalIndex != 0) && (traversalIndex != (Y_GRID-1))) && ( (M < 21 ) && (M > 3) ) ) {
      grid[M].adjacentNeighbours = 0;
      grid[M].adjacentNeighbours = grid[M-1].holdsMine + grid[M+1].holdsMine + grid[ (M + X_GRID) ].holdsMine
                                 + grid[  (M - X_GRID) ].holdsMine + grid[ (M-1) + X_GRID ].holdsMine
                                 + grid[ (M-1) - X_GRID ].holdsMine + grid[ (M+1) + X_GRID ].holdsMine
                                 + grid[ (M+1) - X_GRID ].holdsMine;
      printf("(Index: %d, Adjacent Neighbours: %d)\n", M, grid[M].adjacentNeighbours);
    }
    //index getter for testing
    if(M == index){
      neighbourCount = grid[M].adjacentNeighbours;
    }
  }
  //four corners

  //top & bottom rows

  //left & right columns
  return neighbourCount;
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

enum type { CHAR, INT, BOOL };

int eq(enum type t, int x, int y) {
    static int n = 0;
    n++;
    if (x != y) {
        if (t==CHAR) fprintf(stderr, "\nTest %d gives %c not %c\n", n, x, y);
        if (t==INT) fprintf(stderr, "\nTest %d gives %d not %d\n", n, x, y);
        if (t==BOOL && x) fprintf(stderr, "\nTest %d gives true not false\n", n);
        if (t==BOOL && y) fprintf(stderr, "\nTest %d gives false not true\n", n);
        exit(1);
    }
    return n;
}

int eqc(char x, char y) { return eq(CHAR, x, y); }
int eqi(int x, int y) { return eq(INT, x, y); }
int eqb(bool x, bool y) { return eq(BOOL, x, y); }



/* Unit Testing */

void test(){
  Space grid[X_GRID * Y_GRID] = {{false,0}, {false,1}, {false,1}, {false,1}, {false,1},
                                 {false,1}, {false,3}, {true,3}, {false,3}, {false,1},
                                 {false,1}, {true,1}, {true,2}, {true,1}, {false,1},
                                 {false,1}, {false,2}, {true,3}, {false,3}, {false,1},
                                 {false,0}, {false,1}, {false,1}, {false,1} ,{false,0} };

  Space * s = grid;
  //printf("%lu", sizeof(s));
  eqb(s[0].holdsMine, false);
  eqb(s[7].holdsMine, true);
  eqb(s[4].holdsMine, false);
  eqi(s[12].adjacentNeighbours, 2);
  eqi(s[18].adjacentNeighbours,3);
  //Stage 1

  int x = 0;
  printf("%d\n%d\n", s[4].adjacentNeighbours, grid[4].adjacentNeighbours);
  eqc(s[4].adjacentNeighbours,grid[4].adjacentNeighbours);


  //center square
  eqi(grid[13].adjacentNeighbours, identifyNeighbours(s,13));
  eqi(grid[10].adjacentNeighbours, identifyNeighbours(s,10));
  eqi(grid[18].adjacentNeighbours, identifyNeighbours(s,18));
  eqi(grid[13].adjacentNeighbours, identifyNeighbours(s,13));
  eqi(grid[16].adjacentNeighbours, identifyNeighbours(s,16));

  //left column
  eqi(grid[4].adjacentNeighbours, identifyNeighbours(s,4));

  //right column
  printf("Tests passed: %d\n", eqi(0, 0) - 1);


}


/* EXECUTION */
int main(int argc, char const *argv[]) {
  test();
  return 0;
}
