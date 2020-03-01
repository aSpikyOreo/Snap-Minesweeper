#define M5STACK_MPU6886 
#include <M5Stack.h>

///////////////// ~> MACROS
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240


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
//////////////////
bool locked = false;
//////////////////////
int last_x = 160;
int last_y = 120;

struct circleObj{
  int x_a;
  int y_a;
  bool isMoving;
}; 
typedef struct circleObj Circle;

Circle c;


void setup() {
  // put your setup code here, to run once:
  // Initialize the M5Stack object
  M5.begin();

  M5.Power.begin();
    
  M5.IMU.Init();
  //mine_number = random(1,30); //if this number is chosen then END

  startUp();
  c = startCirclePosition(); //initialise the circle's position
  
  
  delay(5000);
}

Circle startCirclePosition(){
  M5.Lcd.drawCircle(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, 12,WHITE);
  M5.Lcd.fillCircle(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, 10,GREEN);
  c.x_a = SCREEN_WIDTH * 0.5;
  c.y_a = SCREEN_HEIGHT * 0.5;
  c.isMoving = true;
  return c;
}


void regionLock(){
  if((40 < c.x_a and c.x_a < 50) and (30 < c.y_a and c.y_a < 40)){c.isMoving=false;}
  else if((40 < c.x_a and c.x_a < 50) and (115 < c.y_a and c.y_a < 125)){c.isMoving=false;}
  else if((40 < c.x_a and c.x_a < 50) and (205 < c.y_a and c.y_a < 215)){c.isMoving=false;}

  else if((155 < c.x_a and c.x_a < 165) and (30 < c.y_a and c.y_a < 40)){c.isMoving=false;}
  else if((155 < c.x_a and c.x_a < 165) and (205 < c.y_a and c.y_a < 215)){c.isMoving=false;}

  else if((280 < c.x_a and c.x_a < 290) and (30 < c.y_a and c.y_a < 40)){c.isMoving=false;}
  else if((280 < c.x_a and c.x_a < 290) and (115 < c.y_a and c.y_a < 125)){c.isMoving=false;}
  else if((280 < c.x_a and c.x_a < 290) and (205 < c.y_a and c.y_a < 215)){c.isMoving=false;}
  }



void startUp(){
  // Loading Screen....
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN , BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(50,50);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("SNAP MINESWEEPER");  
  M5.Lcd.setCursor(100,150);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("by Leechay Moran-Allen");

  //Loading Squares -> TODO: Increase functionality for squares to appear as route choices as game progresses

  //NOTE: M5Stack screen is 320 x 240
  viewLockingRegions();
  
}

void viewLockingRegions(){
  
  M5.Lcd.drawRoundRect(25,15,40,40, 10,GREEN);
  
  M5.Lcd.drawRoundRect((0.5F*SCREEN_WIDTH - 15),15,40,40, 10,GREEN);

  M5.Lcd.drawRoundRect(265,15,40,40, 10,GREEN);

  M5.Lcd.drawRoundRect(25,(0.5F*SCREEN_HEIGHT - 15),40,40, 10,GREEN);

  M5.Lcd.drawRoundRect(265,(0.5F*SCREEN_HEIGHT - 15),40,40, 10,GREEN);
  
  M5.Lcd.drawRoundRect(25,195,40,40, 10,GREEN);
  
  M5.Lcd.drawRoundRect((0.5F*SCREEN_WIDTH - 15),195,40,40, 10,GREEN);
  
  M5.Lcd.drawRoundRect(265,195,40,40, 10,GREEN);
}

void updateAngles(){
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
//  M5.Lcd.setCursor(0, 10);
//  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", pitch, roll, yaw); // x, y and z angles respectively
//  M5.Lcd.setCursor(150,10 );
//  M5.Lcd.print(" degrees");
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


Circle updateCirclePosition(Circle c){
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
    c.x_a = SCREEN_WIDTH * 0.3F;
    c.y_a = SCREEN_HEIGHT * 0.4F;
    }

  // ball off-screen fix
  if(c.x_a > 319) {c.x_a = 1;}
  else if(c.x_a < 1) {c.x_a = 319;}
  if(c.y_a > 239) {c.y_a = 1;}
  else if(c.y_a < 1) {c.y_a = 239;}

  
  M5.Lcd.setCursor(160,120);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("New data: %d, %d", c.x_a, c.y_a);
  M5.Lcd.drawCircle(c.x_a,c.y_a,12,WHITE);
  M5.Lcd.fillCircle(c.x_a,c.y_a,10,GREEN);

  return c;

  
}


void loop() {
  M5.Lcd.fillScreen(BLACK);
  viewLockingRegions();
  M5.Lcd.setCursor(0,220);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("Moving?: %d ", c.isMoving);
  c = updateCirclePosition(c);
  regionLock();
  // put your main code here, to run repeatedly:
  
  M5.update();
}
