#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
 #include <ESP8266HTTPClient.h>
 #include <ESP8266WiFi.h>

 
#define FIREBASE_HOST "smartbin-110eb.firebaseio.com"
#define FIREBASE_AUTH "tw5KSlGqY0pZC4xPIsc8xGlsaOFzUEO7QPctfdWI"
#define WIFI_SSID "se3nib4nis"
#define WIFI_PASSWORD "pk2757453"

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

const int trigPin = D5;
const int echoPin = D6;
String myString;
float duration, distance;
int sdata = 0;


void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
   Firebase.setString("Variable/Value","smartbin");
 Firebase.setString("Location/latitude","smartbin");
 Firebase.setString("Location/longitude","smartbin");
  Firebase.setInt("PERCENTAGE_STATUS",1);
  Firebase.setString("Location/longitude","smartbin");
 
 
 
 
}

void loop(){
  
  int duration, distance,persentage,value1;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;



      if(  (distance > 0) && (distance <= 10)   ) 
{
 persentage = 100;
 value1=0;
 
 Firebase.setString("DUSTBIN_STATUS","Dustbin Reached The Limit");
} else
if(  (distance > 10) && (distance <= 20)  ) 
{
 
  persentage = 90;
  value1=1;
  Firebase.setString("DUSTBIN_STATUS","Dustbin is Usable");
} else
 
if(  (distance > 20) && (distance <= 30)  ) 
{
 persentage = 80;
 value1=1; 
 Firebase.setString("DUSTBIN_STATUS","Dustbin is Usable");
} else
 
if(  (distance > 30) && (distance <= 40)  ) 
{
 
 persentage = 70;
 value1=1; 
 Firebase.setString("DUSTBIN_STATUS","Dustbin is Usable");
} else
 
if(  (distance > 50) && (distance <= 60)  ) 
{
 persentage = 60;
 value1=1;
 Firebase.setString("DUSTBIN_STATUS","Dustbin is Usable");
} else
 
if(  (distance > 60) && (distance <= 70)  ) 
{
 persentage = 50;
 value1=1; 
 Firebase.setString("DUSTBIN_STATUS","Dustbin is Usable");

} else

if(  (distance > 70) && (distance <= 80)  ) 
{
 persentage = 40;
 value1=1; 
 Firebase.setString("DUSTBIN_STATUS","Dustbin is Usable");
} else

if(  (distance > 80) && (distance <= 90)  ) 
{
 persentage = 30;
 value1=1;
 Firebase.setString("DUSTBIN_STATUS","Dustbin is Usable");
} else

if(  (distance > 90) && (distance <= 100)  ) 
{
 persentage = 20;
 value1=1;
 Firebase.setString("DUSTBIN_STATUS","Dustbin is Usable");
} else

if  (distance > 100)
{
 persentage = 10;
 value1=1;
 Firebase.setString("DUSTBIN_STATUS","Dustbin is Usable");
} 
 


  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);

Firebase.setInt("Variable/Value",persentage );
Firebase.setFloat("Location/latitude",gps.location.lat());
Firebase.setFloat("Location/longitude",gps.location.lng());
Firebase.setInt("PERCENTAGE_STATUS",value1);

delay(1000);       
  
      
    }
  }
}
