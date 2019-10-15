#include "MQ7.h"
MQ7 mq7(A0,5.0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
    int co = mq7.getPPM();
    Serial.println(co);
    delay(3000); 
}
