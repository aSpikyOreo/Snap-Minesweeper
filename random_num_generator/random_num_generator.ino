#define M5STACK_MPU6886 
#include <M5Stack.h> 

/* MACROS */
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240


int loop_count = 0;
void setup() {
  M5.begin();

  M5.Power.begin();
    
  M5.IMU.Init();
  startUp();
  delay(4000);

}

void startUp(){
  M5.Lcd.fillScreen(RED);
  M5.Lcd.setTextColor(0xff80 , RED);
  M5.Lcd.setCursor(30,90);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("RANDOM NUMBER GENERATOR");  
  M5.Lcd.setCursor(90,210);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("by Leechay Moran-Allen");
}


bool flipConfirmed(float currentAngle){
  return(abs(currentAngle) > 170.0F );
}

//void updateAngles(){
//  M5.IMU.getAhrsData(&pitch,&roll,&yaw);
//  M5.IMU.getAccelData(&accX, &accY, &accZ);
//  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
//}

void loop() {
  if(loop_count == 0){
    M5.Lcd.fillScreen(RED);
//    M5.Lcd.drawRoundRect(25,15,285,215, 5,0xff80);
    M5.Lcd.drawRoundRect(20,10,290,220, 5,0xff80);
//    M5.Lcd.drawRoundRect(15,5,295,225, 5,0xff80);
  }
  int rand_num = random(1,20);
//  M5.Lcd.fillScreen(RED);
//  M5.Lcd.drawRoundRect(25,15,285,215, 5,0xff80);
//  M5.Lcd.drawRoundRect(20,10,290,220, 5,0xff80);
//  M5.Lcd.drawRoundRect(15,5,295,225, 5,0xff80);
  M5.Lcd.setCursor(125,90);
  M5.Lcd.setTextSize(7);
  M5.Lcd.printf("%d", rand_num);
  delay(1000);
  loop_count++;
  M5.update();
  // put your main code here, to run repeatedly:
  
}
