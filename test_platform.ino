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
float last_pitch = 0.0F;
float last_roll = 0.0F;

struct circleObj{
  int x_a;
  int y_a;
  float v_x;
  float v_y;
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
  c.v_x = 0.0F;
  c.v_y = 0.0F;
  return c;
}


void identifyRegion(int x_pos, int y_pos){
  int middleVertical = (int) 0.5F*SCREEN_HEIGHT - 15.0F;
  int middleHorizontal = (int) 0.5F*SCREEN_WIDTH-15.0F;
  switch(x_pos){
    case 25:
      switch(y_pos){
        case 30:
          M5.Lcd.printf("Region hit! 25,30");

        case (105):
          M5.Lcd.printf("Region hit! 25,105");

        case 195:
          M5.Lcd.printf("Region hit! 25,195");

        default:
          printf("Invalid coordinates..");
        
      }

    case (140):
      switch(y_pos){
        case 30:
          M5.Lcd.printf("Region hit! 140,30");

        case (105):
          M5.Lcd.printf("Region hit! 140,105");

        case 195:
          M5.Lcd.printf("Region hit! 140,195");

        default:
          printf("Invalid coordinates..");
        
      }


    case 265:
      switch(y_pos){
        case 30:
          M5.Lcd.printf("Region hit! 265,30");

        case (105):
          M5.Lcd.printf("Region hit! 265,105");

        case 195:
          M5.Lcd.printf("Region hit! 265,195");

        default:
          printf("Invalid coordinates..");
        
      }
    default:
      printf("Invalid coordinates...");
  }
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
  
  int ref_pointX;
  int ref_pointY;
  viewLockingRegions();

//  for(int i =0; i< 9; i++){
//    // don't draw @ centre-point
//    
//    if(i != 4){
//    ref_pointX = ( (SCREEN_WIDTH/8) + 70*i )%SCREEN_WIDTH;
//    M5.Lcd.drawPixel(ref_pointX,ref_pointY,GREEN);
//    ref_pointY = ((SCREEN_HEIGHT/8) + 50*i) % SCREEN_WIDTH;
//    }
//  }
  
  
}

void viewLockingRegions(){
  
  M5.Lcd.drawRoundRect(25,15,30,30, 10,GREEN);
  M5.Lcd.drawPixel(40,30,GREEN); //top left
  
  M5.Lcd.drawRoundRect((0.5F*SCREEN_WIDTH - 15),15,30,30, 10,GREEN);
  M5.Lcd.drawPixel(0.5F*SCREEN_WIDTH,30,GREEN); //top middle

  M5.Lcd.drawRoundRect(265,15,30,30, 10,GREEN);
  M5.Lcd.drawPixel(280,30,GREEN); //top right

  M5.Lcd.drawRoundRect(25,(0.5F*SCREEN_HEIGHT - 15),30,30, 10,GREEN);
  M5.Lcd.drawPixel(40,0.5F*SCREEN_HEIGHT,GREEN); //middle left

  M5.Lcd.drawRoundRect(265,(0.5F*SCREEN_HEIGHT - 15),30,30, 10,GREEN);
  M5.Lcd.drawPixel(280,0.5F*SCREEN_HEIGHT,GREEN); //middle right
  
  M5.Lcd.drawRoundRect(25,195,30,30, 10,GREEN);
  M5.Lcd.drawPixel(40,210,GREEN); // bottom left
  
  M5.Lcd.drawRoundRect((0.5F*SCREEN_WIDTH - 15),195,30,30, 10,GREEN);
  M5.Lcd.drawPixel(0.5F*SCREEN_WIDTH,210,GREEN); //bottom middle
  
  M5.Lcd.drawRoundRect(265,195,30,30, 10,GREEN);
  M5.Lcd.drawPixel(280,210,GREEN); //bottom right
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
  float antiJitter = 0.001F; //attempts to reduce overall object sway
  M5.Lcd.setCursor(0,220);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("Accelerometer data: %f, %f", accelX, accelY);
  

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

  // ball off-screen fix
  if(c.x_a > 319) {c.x_a = 1;}
  else if(c.x_a < 1) {c.x_a = 319;}
  if(c.y_a > 239) {c.y_a = 1;}
  else if(c.y_a < 1) {c.y_a = 239;}

  
  M5.Lcd.setCursor(0,20);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("New data: %d, %d", c.x_a, c.y_a);
  M5.Lcd.drawCircle(c.x_a,c.y_a,12,WHITE);
  M5.Lcd.fillCircle(c.x_a,c.y_a,10,GREEN);

  return c;

  
}


void loop() {
  M5.Lcd.fillScreen(BLACK);
  viewLockingRegions();
  c = updateCirclePosition(c);
  identifyRegion(c.x_a, c.y_a);
  // put your main code here, to run repeatedly:
  last_pitch = pitch;
  last_roll = roll;
  

}
