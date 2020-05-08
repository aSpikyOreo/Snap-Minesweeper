#define M5STACK_MPU6886 
#include <M5Stack.h> 

/* MACROS */
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
/* Minesweeper grid dimensions */
#define X_GRID 6 
#define Y_GRID 6 




////////////////// . TODO: Clean up and refactor code to work around using structs and
//////////////////          proper functionality/practice


float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;
//////////////////
float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;
//////////////////
float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;
///////////////////
bool endgame = false;
int loop_count = 0;

struct circleObj{
  int x_a;
  int y_a;
  bool isMoving;
}; 
typedef struct circleObj Circle;
Circle c;

/* Grid Struct */
struct space {
  bool holdsMine; 
  int adjacentNeighbours = 0; //if ¬holdsMine, should have a particular value representing how many neighbours have mines
  int x_pos, y_pos;
  bool flagged;
  bool revealed; 
}; 
typedef struct space Space;

Space grid[X_GRID * Y_GRID];


void setup() {

    // put your setup code here, to run once:
  // Initialize the M5Stack object
  M5.begin();

  M5.Power.begin();
    
  M5.IMU.Init();
  //mine_number = random(1,30); //if this number is chosen then END

  startUp(); 
  delay(5000);
}

void assignMine(){
  int rand_num;
  int mine_count = 0;
  for(int m = 0; m< (X_GRID * Y_GRID); m++){
    rand_num = random(1,20);
    if(rand_num >= 17){
      grid[m].holdsMine = true;
    }
    else{
      grid[m].holdsMine = false;
    }

    grid[m].x_pos = 90 + 25*m;
    grid[m].y_pos = 35 + 25*m;
  }
}

/* kek is this 5-point stencil ?????*/
void identifyNeighbours(){
  int traversalIndex = 0;
  int neighbourCount = 0;

  //inner square
  for(int M = 0 ; M < ( (X_GRID) * (Y_GRID) ); M++) {
    traversalIndex = M % Y_GRID;

    //checks if pointing at top or bottom row value
    if( ((traversalIndex != 0) && (traversalIndex != (Y_GRID-1))) && ( (M <= ((Y_GRID)*(X_GRID-1)-1) ) && (M >= (Y_GRID+1) ) ) ) {
      grid[M].adjacentNeighbours = 0;
      grid[M].adjacentNeighbours = grid[M-1].holdsMine + grid[M+1].holdsMine + grid[ (M + Y_GRID) ].holdsMine
                                 + grid[  (M - Y_GRID) ].holdsMine + grid[ (M-1) + Y_GRID ].holdsMine
                                 + grid[ (M-1) - Y_GRID ].holdsMine + grid[ (M+1) + Y_GRID ].holdsMine
                                 + grid[ (M+1) - Y_GRID ].holdsMine;
      //printf("(Index: %d, Adjacent Neighbours: %d)\n", M, grid[M].adjacentNeighbours);
    }

    //four corners
    grid[0].adjacentNeighbours = grid[Y_GRID].holdsMine + grid[(Y_GRID + 1)].holdsMine + grid[1].holdsMine;  //top right

    grid[(Y_GRID - 1)].adjacentNeighbours = grid[ (Y_GRID - 1) - 1 ].holdsMine + grid[(Y_GRID - 1) + Y_GRID].holdsMine
                                          + grid[(Y_GRID - 1) + Y_GRID - 1].holdsMine; //bottom left

    grid[(X_GRID * Y_GRID - 1)].adjacentNeighbours = grid[ (X_GRID * Y_GRID - 1) - 1 ].holdsMine + grid[ (X_GRID * Y_GRID - 1) - Y_GRID].holdsMine
                                               + grid[ (X_GRID * Y_GRID - 1) - (Y_GRID + 1)].holdsMine; //bottom right

    grid[ (X_GRID * (Y_GRID - 1)) ].adjacentNeighbours = grid[ (X_GRID * (Y_GRID - 1)) + 1 ].holdsMine
                                                       + grid[ (X_GRID * (Y_GRID - 1)) - Y_GRID].holdsMine
                                                       + grid[ (X_GRID * (Y_GRID - 1)) - (Y_GRID) + 1].holdsMine; //bottom left

    //top & bottom rows

    //left & right columns

    for(int K = 1; K < Y_GRID-1; ++K){
      //left column
      grid[K].adjacentNeighbours = grid[K-1].holdsMine
                                 + grid[K+1].holdsMine
                                 + grid[(K+Y_GRID)].holdsMine
                                 + grid[(K+Y_GRID) - 1].holdsMine
                                 + grid[(K+Y_GRID) + 1].holdsMine;

      //right column
      grid[ (X_GRID * (Y_GRID - 1)) + K ].adjacentNeighbours = grid[ (X_GRID * (Y_GRID - 1)) + K + 1 ].holdsMine
                                                             + grid[ (X_GRID * (Y_GRID - 1)) + K - 1 ].holdsMine
                                                             + grid[ (X_GRID * (Y_GRID - 1)) + K - Y_GRID ].holdsMine
                                                             + grid[ (X_GRID * (Y_GRID - 1)) + K - Y_GRID + 1 ].holdsMine
                                                             + grid[ (X_GRID * (Y_GRID - 1)) + K - Y_GRID - 1 ].holdsMine;


      //top row
      grid[K*Y_GRID].adjacentNeighbours = grid[K*Y_GRID + 1].holdsMine + grid[(K+1)*Y_GRID].holdsMine + grid[(K-1)*Y_GRID].holdsMine
                                        + grid[K*Y_GRID + 1 - Y_GRID].holdsMine + grid[K*Y_GRID + 1 + Y_GRID].holdsMine;



      //bottom row
      grid[(K+1)*(Y_GRID) - 1 ].adjacentNeighbours = grid[(K+1)*(Y_GRID) - 1 - 1].holdsMine
                                                   + grid[(K+1)*(Y_GRID) - 1 - Y_GRID].holdsMine
                                                   + grid[(K+1)*(Y_GRID) - 1 + Y_GRID].holdsMine
                                                   + grid[(K+1)*(Y_GRID) - 1 - Y_GRID - 1].holdsMine
                                                   + grid[(K+1)*(Y_GRID) - 1 + Y_GRID - 1].holdsMine;
    }



//    //index getter for testing
//    if(M == index){
//      neighbourCount = grid[M].adjacentNeighbours;
//    }
  }
//  return neighbourCount;
}


void regionLock(){
  int x_shift, y_shift;
  for(int ii = 0; ii < X_GRID; ii++ ){
    x_shift = 25 * ii;
    for(int jj = 0; jj < Y_GRID; jj++){
      y_shift = 25* jj; 
      if(( (97 + x_shift) < c.x_a and c.x_a < (107 + x_shift) ) and ( (43+y_shift) < c.y_a and c.y_a < (53+y_shift) )){
        if(M5.BtnC.wasPressed()){
          c.isMoving=false;
        }
      }
    }
  }
}

  



void startUp(){
  // Loading Screen....
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN , BLACK);
  M5.Lcd.setCursor(80,10);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("SNAP MINESWEEPER");  
  M5.Lcd.setCursor(90,210);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("by Leechay Moran-Allen");

  //Loading Squares -> TODO: Increase functionality for squares to appear as route choices as game progresses

  //NOTE: M5Stack screen is 320 x 240
  viewLockingRegions();
  assignMine();
  identifyNeighbours();
  
}

//view the grid
void viewLockingRegions(){
  int x_shift, y_shift;
  for(int ii = 0; ii < X_GRID; ii++ ){ 
    x_shift = 25 * ii;
    for(int jj = 0; jj < Y_GRID; jj++){
      y_shift = 25* jj;


      //cheat-mode
      if(grid[Y_GRID*ii + jj].holdsMine == true){
        M5.Lcd.drawRoundRect(90 + x_shift,35+y_shift,25,25, 5,GREEN);
        M5.Lcd.fillRoundRect(90 + x_shift,35+y_shift,23,23, 5,RED);
      }

      
      else if(grid[Y_GRID*ii + jj].revealed) {
        M5.Lcd.setTextColor(GREEN,BLACK);
        M5.Lcd.setTextSize(1);
        M5.Lcd.setCursor(90 + x_shift + 1,35+y_shift + 10 );
        M5.Lcd.printf(" %d ", grid[Y_GRID*ii + jj].adjacentNeighbours);
      }
      else{
         M5.Lcd.drawRoundRect(90 + x_shift,35+y_shift,25,25, 5,GREEN);
         M5.Lcd.fillRoundRect(90 + x_shift,35+y_shift,23,23, 5,0x7bef);
      }
    }
    
  }
}



//if the circle is within the grid, draw over that particular circle

//if the circle is not inside that grid, draw black over it's last position




//once locked, flip M5Stack upside down to confirm position
bool moveConfirmed(float currentAngle){
  return(abs(currentAngle) > 170.0F );
}

//find the space the circle is locked in using its co-ordinates
int getSpaceIndex(int circle_x, int circle_y){
  
  int index = 0;
  int rem_x = 0;
  int rem_y = 0;

  rem_x = int((circle_x - 90)*0.04F);
  rem_y = int((circle_y -35)*0.04F);


  index = Y_GRID*rem_x + (rem_y);
  return index;
}


// after a move is confirmed, reveal space and determine the game progression's next steps
// any neighbouring spaces with zero neighbours should also be unveiled

void determineOutcome(Circle c){
  int index;
  index = getSpaceIndex(c.x_a, c.y_a);
  if(moveConfirmed(roll) and c.isMoving == false){
    if(grid[index].holdsMine == true){
      endgame = true;
    }
    else{
      grid[index].revealed = true;
      
    }
  }
}


//updates values holding key accelerometer, gyroscope, & rotational data
void updateAngles(){
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
}

float computeAccel(char axis){
  float res = 0.0F;
  updateAngles();
  switch(axis)
  {
    case 'X':
      res = accX;
      return res;

    case 'Y':
      res = accY;
      return res;

    case 'Z':
      res = accZ;
      return res;
    }
  return 0.0F;
  
}

Circle updateCirclePosition(Circle c, int prevX, int prevY){
  float accelX = computeAccel('X');
  float accelY = computeAccel('Y');
  float antiJitter = 0.01F; //attempts to reduce overall object sway

  if(c.isMoving){
    // invert axis for easier usability
    if((accelX - antiJitter) > 0.0F){
      c.x_a -= 1;    
    }
    else if((accelX + antiJitter) < 0.0F){
      c.x_a += 1;    
    }
    if((accelY - antiJitter) > 0.0F){
      c.y_a += 1;    
    }
    else if((accelY + antiJitter) < 0.0F){
      c.y_a -= 1;    
    }

  }

  if(M5.BtnB.wasPressed()){
    c.isMoving =true;
    c.x_a = SCREEN_WIDTH * 0.5F;
    c.y_a = SCREEN_HEIGHT * 0.8F;
    }

  // ball off-screen fix
  if(c.x_a > 319) {c.x_a = 1;}
  else if(c.x_a < 1) {c.x_a = 319;}
  
  if(c.y_a > 239) {c.y_a = 1;}
  else if(c.y_a < 1) {c.y_a = 239;}

  M5.Lcd.drawCircle(c.x_a,c.y_a,5,WHITE);
  M5.Lcd.fillCircle(c.x_a,c.y_a,3,GREEN);
  M5.Lcd.drawCircle(prevX,prevY,5,BLACK);
  M5.Lcd.fillCircle(prevX,prevY,3,BLACK);

  return c;

  
}

void fillBackground(int prevX, int prevY){
  if( !((c.x_a > 90 && c.x_a < 215) && (c.y_a > 35 && c.y_a < 160)) ){
    M5.Lcd.drawCircle(prevX, prevY,5,BLACK);
    M5.Lcd.fillCircle(prevX, prevY,3,BLACK);
  }
  
}

void loop() {
  int lastX, lastY;
  if(!endgame){
    if(loop_count == 0){
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0,220);
      M5.Lcd.setTextSize(1);
      
    }
    if(loop_count > 0){
      lastX = c.x_a;
      lastY = c.y_a;
    }
    viewLockingRegions();
//  M5.Lcd.fillScreen(BLACK);
//  viewLockingRegions();
//  M5.Lcd.setCursor(0,220);
//  M5.Lcd.setTextSize(1);
//  M5.Lcd.printf("Current Space No: %d ", getSpaceIndex(c.x_a, c.y_a));
  c = updateCirclePosition(c, lastX,lastY);
  fillBackground(lastX,lastY);
//  fillSquares(c);
  regionLock();
  determineOutcome(c);
  loop_count++;
  delay(20);
  M5.update();
  }
  else{
    M5.Lcd.fillScreen(WHITE);
    M5.Lcd.setTextColor(BLUE , WHITE);
    M5.Lcd.setCursor(50,150);
    M5.Lcd.setTextSize(2);
    M5.Lcd.printf("GAME OVER");
  }
}
