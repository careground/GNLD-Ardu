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
   if (BTSerial.available()) {
    int data = BTSerial.read();
    Serial.println(data);
 
    if(data == 49) {   // BT 로 1 이 오면 (1==49) 로 치환됨
      digitalWrite(LED,HIGH);
    }else{
      digitalWrite(LED,LOW);
    }
  }
 
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }
}
