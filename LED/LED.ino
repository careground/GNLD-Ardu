#include <pm2008_i2c.h>

PM2008_I2C pm2008_i2c;

#define RED 4
#define YELLOW 5
#define GREEN 6

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
  pm2008_i2c.begin();
  Serial.begin(9600);
  pm2008_i2c.command();
  delay(1000);
}

void loop() {
  uint8_t ret = pm2008_i2c.read();

  uint8_t pm1p0_grade = 0;
  uint8_t pm2p5_grade = 0;
  uint8_t pm10p_grade = 0;
  uint8_t total_grade = 0;

  if (ret == 0) {
    // PM 1.0
    if (pm2008_i2c.pm1p0_grimm < 16) {
      pm1p0_grade = 1;
    } else if (pm2008_i2c.pm1p0_grimm < 51) {
      pm1p0_grade = 2;
    } else if (pm2008_i2c.pm1p0_grimm < 101) {
      pm1p0_grade = 3;
    } else {
      pm1p0_grade = 4;
    }

    // PM 2.5
    if (pm2008_i2c.pm2p5_grimm < 16) {
      pm2p5_grade = 1;
    } else if (pm2008_i2c.pm2p5_grimm < 51) {
      pm2p5_grade = 2;
    } else if (pm2008_i2c.pm2p5_grimm < 101) {
      pm2p5_grade = 3;
    } else {
      pm2p5_grade = 4;
    }

    // PM 10
    if (pm2008_i2c.pm10_grimm < 31) {
      pm10p_grade = 1;
    } else if (pm2008_i2c.pm10_grimm < 81) {
      pm10p_grade = 2;
    } else if (pm2008_i2c.pm10_grimm < 151) {
      pm10p_grade = 3;
    } else {
      pm10p_grade = 4;
    }

    // Get worst grade
    total_grade = max(pm1p0_grade, pm2p5_grade);
    total_grade = max(total_grade, pm10p_grade);

    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);

    switch (total_grade) {
      case 1: {
          Serial.println("Good!");
          digitalWrite(GREEN, HIGH);
          break;
        }
      case 2: {
          Serial.println("Normal!");
          digitalWrite(GREEN, HIGH);
          break;
        }
      case 3: {
          Serial.println("Bad!");
          digitalWrite(YELLOW, HIGH);
          break;
        }
      case 4: {
          Serial.println("Worst!");
          digitalWrite(RED, HIGH);
          break;
        }
      default:
        break;
    }
  }
  delay(3000);
}
