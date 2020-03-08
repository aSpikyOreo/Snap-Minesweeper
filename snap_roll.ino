#define M5STACK_MPU6886 

#include <M5Stack.h>

/*
TODO:Stream the orientation char of the M5Stack to the SD Card and upload that as a JSON with the following structure: 

M5[
  Turn: 1
  State: 'U' -> for UP
  Number: 17
  Player: 2
  ]




*/

float pitch = 0.0F;
float roll = 0.0F;
float yaw = 0.0F;

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;


int starting_number = 0;
int targetNum = 40;
int turns = 0;
bool endGame = false;


enum state { _UP_ = 0, _RIGHT_ = 1, _DOWN_ = 2, _LEFT_ = 3,} check;


void setup() {
  // M5 setup
  M5.begin();
  M5.Power.begin();

  // Setup the IMU
  M5.IMU.Init();

  // Setup screen
  startUp();
}

bool isUp(){
  return( (pitch <= -8.0F and pitch >= -15.0F) and (roll >= 0) and (accY > 0.98F) );
}

bool isRight(){
  return( (pitch <= 75.0F and pitch >= 65.0F) and (roll >= 0) and (accX < -0.98F) );
}

bool isUpsideDown(){
  return( (pitch >= 8.0F and pitch <= 15.0F) and (roll < 0) and (accY < -0.98F) );
}

bool isLeft(){
  return( (pitch >= -75.0F and pitch <= -65.0F) and (roll < 0) and (accX > 0.98F) );
}


char identifyState(){
  if(isUp()){return 'U';} //UP
  if(isUpsideDown()){return 'D';} //Down
  if(isLeft()){return 'L';} //LEFT
  if(isRight()){return 'R';} //RIGHT
  
}


void updateAngles(){
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);
  M5.IMU.getAccelData(&accX,&accY,&accZ);
}

void startUp(){
  M5.Lcd.fillScreen(0xff80);
  M5.Lcd.setTextColor(RED , 0xff80);
  M5.Lcd.setTextSize(1);

  M5.Lcd.setCursor(50,50);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("ROLLING SNAP");  
  M5.Lcd.setCursor(100,150);
  M5.Lcd.setTextSize(1);
  M5.Lcd.printf("by Leechay Moran-Allen");
  delay(3000);
}


int increment_atTurn(char state){
  int res = 0;
  
  switch(state)
  {
      case 'U':
          res = 2;
          return res;
      case 'D':
          res = 1;
          return res;
      case 'L':
          res = 1;
          return res;
      case 'R':
          res = 2;
          return res; 
    }
    return 0;  
  
}

void loop() {
  char currentState, previousState;
  int targetNum = 400;
  int player;
  if(!endGame){
    M5.Lcd.fillScreen(0xff80);
    M5.Lcd.setCursor(140,100);
    M5.Lcd.setTextSize(4);
    M5.Lcd.printf("%d", starting_number); 
    currentState = identifyState();
    updateAngles();
    
    if(previousState != currentState){
      
      starting_number += increment_atTurn(currentState);
      turns += 1;
    }
  
    //update last state transition
    previousState = currentState;
  
  
    if(starting_number >= targetNum){
      endGame = true;
    }
  }
    if(endGame == true){
      player = (turns % 4) + 1;
      M5.Lcd.fillScreen(RED);
      M5.Lcd.setTextColor(0xff80 , RED);
      M5.Lcd.setCursor(50,100);
      M5.Lcd.setTextSize(2);
      M5.Lcd.printf("GAME OVER. Player %d has won!", player);
    }

    delay(10);
      
  }
  
  
