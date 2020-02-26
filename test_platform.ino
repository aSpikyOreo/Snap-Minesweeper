#define M5STACK_MPU6886 
#include <M5Stack.h>
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

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN , BLACK);
  M5.Lcd.setTextSize(1);

  M5.Lcd.setCursor(50,50);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("SNAP MINESWEEPER");  
  M5.Lcd.setCursor(100,150);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("by Leechay Moran-Allen");
  c = startCirclePosition();
  delay(5000);
}

Circle startCirclePosition(){
  M5.Lcd.drawCircle(160, 120, 12,WHITE);
  M5.Lcd.fillCircle(160, 120, 10,GREEN);
  c.x_a = 160;
  c.y_a = 120;
  c.v_x = 0.0F;
  c.v_y = 0.0F;
  return c;
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
  c = updateCirclePosition(c);
  // put your main code here, to run repeatedly:
  last_pitch = pitch;
  last_roll = roll;
  

}
