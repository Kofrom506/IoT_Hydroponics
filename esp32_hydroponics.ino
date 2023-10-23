#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include "FirebaseESP32.h"
#include <HTTPClient.h>

#define FIREBASE_HOST "esp32firebase-41756-default-rtdb.asia-southeast1.firebasedatabase.app/" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "0pW10m4BpTRZntfQsgfKSbFedqHc0rHGCCuVYqkR"

const char* ssid = "Kopiko";
const char* password = "internet123";


const int pHPin = 4;
const int ECPin = 5;
const int tempPin = 6;
const int pumpPins[] = {8, 9, 10};

Adafruit_ADS1115 ads;
OneWire oneWire(tempPin);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  ads.begin();
  sensors.begin();

  for (int i = 0; i < 3; i++) {
    pinMode(pumpPins[i], OUTPUT);
    digitalWrite(pumpPins[i], LOW); // Turn off the pumps initially
  }
}

void loop() {
  // Read sensor values
  float pHValue = readPHSensor();
  float ecValue = readECSensor();
  float tempValue = readTemperatureSensor();

  controlPumps(ecValue);

  sendDataToDatabase(pHValue, ecValue, tempValue);
  
  delay(10000); 
}

float readPHSensor() {
  analogRead(pHPiN);
  return 0.0;
}

float readECSensor() {
  analogRead(ECPin);
  return 0.0;
}

float readTemperatureSensor() {
  analogRead(temperaturePin);
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

void controlPumps(float ecValue) {
  if(pHValue>100){
    digitalWrite(8,HIGH);
  } 
  if(ecValue>100){
    digitalWrite(8,HIGH);
  } 
   if(tempValue>100){
    digitalWrite(8,HIGH);
  } 
  
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
}

void sendDataToDatabase(float pHValue, float ecValue, float tempValue) {
  
}
