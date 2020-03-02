// M5Stack Functionality
#define M5STACK_MPU6886 
#include <M5Stack.h> 

//WiFi Functionality for ESP devices
#include <HTTPClient.h>
#include <WiFi.h>

const char* ssid = "ctrl-alt-just_me";
const char* password = "lee.chay2";

void setup() {
  M5.begin();
  Serial.begin(115200);                 //Serial connection
  WiFi.begin(ssid, password);   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(1000);
    Serial.println("Connecting to Wi-Fi..");
 
  }
  Serial.println("Connected to Wi-Fi!");
}


void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http_recv;  //Declare an object of class HTTPClient
 
    http_recv.begin("http://192.168.43.75:8090/helloesp"); //Specify request destination
 
    int httpCodeA = http_recv.GET(); //Send the request
 
    if (httpCodeA > 0) { //Check the returning code
 
      String payloadA = http_recv.getString();   //Get the request response payload
      Serial.println(payloadA);             //Print the response payload
 
    }else Serial.println("An error ocurred");
 
    http_recv.end();   //Close connection
 
  }
 
  delay(10000);    //Send a request every 10 seconds
 
}
