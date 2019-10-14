#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); 
int LED = 8;
void setup()  
{
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Serial.println("Hello!");
  BTSerial.begin(9600);  // set the data rate for the BT port
}
  
void loop()
{
  //폰 -> 아두이노 (참고용)
   if (BTSerial.available()) {
    int data = BTSerial.read();
    Serial.println(data);
 
    if(data == 49) {   // BT 로 1 이 오면 (1==49) 로 치환됨
      digitalWrite(LED,HIGH);
    }else{
      digitalWrite(LED,LOW);
    }
  }

 //아두이노 -> 폰
 //BTSerial.write("데이터");
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
}
