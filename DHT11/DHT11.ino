// Modified by John 2015 11 03
// MIT license

#include "DHT.h"  //DHT-22센서를 사용하기위하여 라이브러리를 불러옵니다.
 /*8번 PIN에서 데이터가 들어오고, 센서는 DHT22 센서를 사용한다고 정의합니다. */
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); //PC모니터를 이용하기 위하여, 시리얼통신을 정의해줍니다.
   dht.begin(); //DHT22센서의 사용시작을 정의해줍니다.
}
void loop() {
  delay(2000); //측정하는 시간사이에 2초간의 딜레이를 줘야 합니다.
  float h = dht.readHumidity(); //습도값을 읽어온후 h변수값에 값을 저장합니다. 
  float t = dht.readTemperature();  //온도값을 읽어온후 t변수값에 값을 저장합니다. 
  float hic = dht.computeHeatIndex(t, h, false); /*DHT22는 열지수(체감온도) 를 나타내줄수있는 함수가 포함되어있습니다. */
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("\t");
  Serial.print("Heat index: ");
  Serial.print(hic); //열지수(체감온도)가 출력됩니다.
  Serial.println(" *C ");
}
