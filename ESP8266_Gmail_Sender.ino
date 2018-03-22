#include <ESP8266WiFi.h>
#include "Gsender.h"

#pragma region Globals
const char* ssid = "red";                           // WIFI network name
const char* password = "red12345";                       // WIFI network password
uint8_t connection_state = 0;                    // Connected to WIFI or not
uint16_t reconnect_interval = 10000;             // If not connected wait time to try again
#pragma endregion Globals
int LED = D1; 
int BUZZER=D2;
int obstaclePin = D5;  
int hasObstacle = HIGH; 

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
    static uint16_t attempt = 0;
    Serial.print("Connecting to ");
    if(nSSID) {
        WiFi.begin(nSSID, nPassword);  
        Serial.println(nSSID);
    } else {
        WiFi.begin(ssid, password);
        Serial.println(ssid);
    }

    uint8_t i = 0;
    while(WiFi.status()!= WL_CONNECTED && i++ < 50)
    {
        delay(50);
        Serial.print(".");
    }
    ++attempt;
    Serial.println("");
    if(i == 51) {
        Serial.print("Connection: TIMEOUT on attempt: ");
        Serial.println(attempt);
        if(attempt % 2 == 0)
            Serial.println("Check if access point available or SSID and Password\r\n");
        return false;
    }
    Serial.println("Connection: ESTABLISHED");
    Serial.print("Got IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}

void Awaits()
{
    uint32_t ts = millis();
    while(!connection_state)
    {
       // delay(50);
        if(millis() > (ts + reconnect_interval) && !connection_state){
            connection_state = WiFiConnect();
            ts = millis();
        }
    }
}

void setup()
{
    Serial.begin(115200);
      pinMode(LED, OUTPUT);
  pinMode(obstaclePin, INPUT);
    connection_state = WiFiConnect();
    if(!connection_state)  // if not connected to WIFI
        Awaits();          // constantly trying to connect

    // Getting pointer to class instance
    
}

void loop(){
  hasObstacle = digitalRead(obstaclePin);     

  if (hasObstacle == HIGH) 
  {
    digitalWrite(LED, HIGH);
    analogWrite(BUZZER, HIGH);
      Gsender *gsender = Gsender::Instance();
      String subject = "Securty breach";
      gsender->Subject(subject)->Send("rameshnaidu9087@gmail.com", "ALERT: AN OBSTACLE FOUND");
      gsender->Subject(subject)->Send("massbunkers2020@gmail.com", "ALERT: AN OBSTACLE FOUND");
        Serial.println("Message send.");
       // delay(100);
      }
  else
  {
    digitalWrite(LED, LOW);
    analogWrite(BUZZER, LOW);
    delay(100);
  }

  }
