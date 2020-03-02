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
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://192.168.43.75:8090/hello"); //Specify request destination
    http.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
   int httpCode = http.POST("Message from M5Stack!");   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
  }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(10000);    //Send a request every 10 seconds
 
}
