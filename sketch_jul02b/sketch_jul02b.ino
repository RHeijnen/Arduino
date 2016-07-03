#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//"BUILTIN_LED" WEMOS has a builtin led cool cool cool

const char* network     = "FBI Surveillance Van";      
const char* passw = "1234567890";  
int sensorPin = 3;
byte dat[5];
WiFiClient client;
String result;

byte read_data(){
  byte data;
  for (int i = 0; i < 8;i++){
    if(digitalRead (sensorPin) == LOW){
      while(digitalRead (sensorPin) ==LOW){
        delayMicroseconds (30);
        if (digitalRead (sensorPin) == HIGH){
          data |= (1 <<(7-i));
          while(digitalRead (sensorPin) == HIGH){
            
          }
        }
      }
    }
  }
  return data;
}

void getReading(){
  digitalWrite(sensorPin,LOW);
  delay(30);

  digitalWrite(sensorPin,HIGH);
  delayMicroseconds(40);

  pinMode(sensorPin,INPUT);
  while(digitalRead (sensorPin) == HIGH){
    delayMicroseconds (80);
  }
  if(digitalRead (sensorPin) == LOW){
    delayMicroseconds (80);
  }
  for(int i = 0; i < 4 ;i++){
    dat[i] = read_data();
  }
  pinMode(sensorPin, OUTPUT);
  digitalWrite(sensorPin,HIGH);
}


void setup() {
  Serial.begin(9600);
  pinMode(sensorPin,OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(); // kill previous just to be sure
  delay(200);        // waiting for the mode to initiate and the killing to be done
  WiFi.begin(network, passw); // after the delay it should be safe to start up now

  
while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    delay(10);
    Serial.print(".");
    delay(10);
    Serial.print(".");
  }

  Serial.print("\nConnected to: ");
  Serial.println(network);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  Serial.println("Connected");
  delay(1000);
}
  


void loop() {

getReading();
Serial.println();
Serial.print("Humidity = ");
Serial.print(dat[0],DEC);
Serial.print(" . ");
Serial.print(dat[1],DEC);
Serial.println(" % ");
Serial.print(" temperature = ");
Serial.print(dat[2],DEC);
Serial.print(" . ");
Serial.print(dat[3],DEC);
Serial.println("C");






}
