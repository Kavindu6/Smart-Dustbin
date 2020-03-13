#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Servo.h>
 
#define FIREBASE_HOST "smartbin-110eb.firebaseio.com"
#define FIREBASE_AUTH "tw5KSlGqY0pZC4xPIsc8xGlsaOFzUEO7QPctfdWI"
#define WIFI_SSID "se3nib4nis"
#define WIFI_PASSWORD "pk2757453"

 
Servo servo1;
int trigPin=D1;
int echoPin=D2;
long distance;
long duration;
 
void setup(){
    
    servo1.attach(D3);
   
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
   
   Serial.begin(115200);
   
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

Serial.print("connecting");

while (WiFi.status() != WL_CONNECTED) {

Serial.print(".");

delay(500);

}

Serial.println();

Serial.print("connected: ");

Serial.println(WiFi.localIP());                                    
   
    Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
    Firebase.set("SERVO_STATUS",1);
}
 
void loop(){
   
    int n=Firebase.getInt("SERVO_STATUS");
   
    if(n==1){
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration=pulseIn(echoPin, HIGH);
        distance=duration*0.034/2;
       
        servo1.write(0);
       
        if(distance<=10){
            servo1.write(85);
            delay(3000);
        }
    }else{
        servo1.write(0);
    }
}
