#define M5STACK_MPU6886 
#include <M5Stack.h>

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

float temp = 0.0F;

int mine_number = 0;
bool endGame = false;
//reference_to_last_y_axis_angle
float lastRoll = 0.0F;

// the setup routine runs once when M5Stack starts up

//updates on-screen angle values drawn from accelerometer
void updateAngles(){
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", pitch, roll, yaw); // x, y and z angles respectively
  M5.Lcd.setCursor(150,10 );
  M5.Lcd.print(" degrees");
}

//verifies if a significant turn has been made
//bool verifyFlip(int new_angle,int old_angle){
//  int difference = new_angle - old_angle;
//  return(difference > 90);
//}

bool faceDown(float currentAngle){
  return(abs(currentAngle) > 170.0F );
}





void setup(){

  // Initialize the M5Stack object
  M5.begin();
  /*
    Power chip connected to gpio21, gpio22, I2C device
    Set battery charging voltage and current
    If used battery, please call this function in your project
  */
  M5.Power.begin();
    
  M5.IMU.Init();
  //mine_number = random(1,30); //if this number is chosen then END

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN , BLACK);
  M5.Lcd.setTextSize(1);
}

// the loop routine runs over and over again forever
void loop() {
  if(!endGame){
  bool hasFlipped = false;
  updateAngles();
  M5.Lcd.setCursor(50,150);
  M5.Lcd.printf("Previous %5.2f, Current %5.2f", lastRoll, roll);
  hasFlipped = faceDown(roll);
  if(hasFlipped){
     mine_number = random(1,30);
     M5.Lcd.fillScreen(RED);
     M5.Lcd.setTextColor(WHITE , RED);
  }
  else{
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(GREEN , BLACK);
    if(mine_number > 26){
      endGame = true;
      M5.Lcd.fillScreen(WHITE);
      M5.Lcd.setTextColor(BLUE , WHITE);
      M5.Lcd.setCursor(50,150);
      M5.Lcd.setTextSize(2);
      M5.Lcd.printf("GAME OVER");
      }
      
    
  }
  lastRoll = roll;
  delay(1);
  }
}
