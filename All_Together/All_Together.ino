#include <SoftwareSerial.h>
#include "DHT.h" 
#include <ArduinoJson.h>

#define DHTPIN 4
#define DHTTYPE DHT22
int LED = 8;
int tempLimit = 20;

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial BTSerial(2, 3); 

void setup()  
{
  Serial.begin(9600);
  Serial.println("Hello!");
  dht.begin();
  BTSerial.begin(9600);  // set the data rate for the BT port
}
  
void loop()
{
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

//  float hic = dht.computeHeatIndex(t, h, false); /*DHT22는 열지수(체감온도) 를 나타내줄수있는 함수가 포함되어있습니다. */
    
  delay(3000); //3초마다 반복
  StaticJsonDocument<200> doc;
  doc["temperature"] = temp;
  doc["humidity"] = humidity;
  serializeJson(doc, BTSerial);
  BTSerial.println();

  if(temp > tempLimit) {   
      digitalWrite(LED,HIGH);
    }else{
      digitalWrite(LED,LOW);
    }
}
