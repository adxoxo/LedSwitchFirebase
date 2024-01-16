#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define LED_PIN D0

#define API_KEY "AIzaSyDDQlkaGTSRTLTcmvK10MBYqX_YZWcloPo"
#define DATABASE_URL "https://ledswitch-7f583-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define PROJECT_ID "ledswitch-7f583"

#define WIFI_SSID "Gemenez_2.4ghz"
#define WIFI_PASSWORD "LifeIsHere"

#define USER_EMAIL "sd@gmail.com"
#define USER_PASSWORD "123456"
int _state;
FirebaseData fbase;
FirebaseAuth auth;
FirebaseConfig config;

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ...");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();

  pinMode(LED_PIN, OUTPUT);

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  config.token_status_callback = tokenStatusCallback;
  config.max_token_generation_retry = 5; 

  Firebase.begin(&config, &auth);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Firebase.RTDB.getInt(&fbase, "state", &_state)); else Serial.println("FAILED: " + fbase.errorReason());
  Serial.print(_state);

  if (_state == 1){
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}