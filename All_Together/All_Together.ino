#include <SoftwareSerial.h>
#include "DHT.h" 
#include "MQ7.h"
#include <ArduinoJson.h>
#include <pm2008_i2c.h>

#define DHTTYPE DHT22
#define BLE_TX 2
#define BLE_RX 3
#define DHTPIN 4
#define MQ7PIN A0
#define SOILPIN A1
#define RED 5 //일산화탄소
#define YELLOW 6 //미세먼지
#define GREEN 7 //토양수분

int coLimit = 10; //일산화탄소 10ppm 이상 위험
int dustLimit_pm10 = 100; //pm10 100㎍/㎥ 이상 위험
int dutLimit_pm2p5 = 50; //pm2.5 50㎍/㎥ 이상 위험
int soilHumidityLimit = 35; //토양 수분 35% 미만 위험

SoftwareSerial BTSerial(BLE_TX, BLE_RX); 
DHT dht(DHTPIN, DHTTYPE);
MQ7 mq7(MQ7PIN,5.0);
PM2008_I2C pm2008_i2c;

void setup()  
{
  Serial.begin(9600);
  Serial.println("Hello!");
  BTSerial.begin(9600);  // set the data rate for the BT port BTSerial
  dht.begin();
  pm2008_i2c.begin();
  pm2008_i2c.command();
  
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

  
void loop()
{
  //공기중 습도(단위 %) / 온도 (단위 °C)
  float humidity_per = dht.readHumidity();
  float temp = dht.readTemperature();
  //float hic = dht.computeHeatIndex(t, h, false); //체감온도
  
  //일산화탄소 농도 (단위 ppm)
  int co = mq7.getPPM();
  int pm10 = 0;
  int pm2p5 = 0;

  uint8_t ret = pm2008_i2c.read();
  if (ret == 0) {
    pm10 = pm2008_i2c.pm10_grimm;
    pm2p5 = pm2008_i2c.pm2p5_tsi;
  }

  int nsoil = analogRead(SOILPIN); //토양습도 센서값 
  int nsoil_per = map(nsoil,170, 1023, 100, 0); //센서값을 %로 변경
    
  delay(3000); //3초마다 반복
  StaticJsonDocument<200> doc;
  doc["temperature"] = temp;
  doc["humidity_percent"] = humidity_per;
  doc["CO"] = co;
  doc["pm10"] = pm10;
  doc["pm2p5"] = pm2p5;
  doc["soil_percent"] = nsoil_per;
  serializeJson(doc, BTSerial);
  BTSerial.println();

  //일산화탄소 높을때 red led 출력
  if(co > coLimit) {   
      digitalWrite(RED,HIGH);
    }else{
      digitalWrite(RED,LOW);
    }
   //미세먼지 높을때 yellow led 출력
    if(pm10 > dustLimit_pm10 || pm2p5 > dutLimit_pm2p5) {   
      digitalWrite(YELLOW,HIGH);
    }else{
      digitalWrite(YELLOW,LOW);
    }
    //토양 습도 낮을때 green led 출력
    if(nsoil_per < soilHumidityLimit) {   
      digitalWrite(GREEN,HIGH);
    }else{
      digitalWrite(GREEN,LOW);
    }
}
