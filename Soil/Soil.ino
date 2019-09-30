const int nPin_soil = A0; // A0: 토양습도 센서

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  int nsoil = analogRead(nPin_soil);
  int nsoilper = map(nsoil,170, 1023, 100, 0); //센서값을 %로 변경

  Serial.print("sensnr : ");
  Serial.print(nsoil); //토양습도 센서값 시리얼 출력
  Serial.print("\t map : ");
  Serial.println(nsoilper); //토양습도 센서값 %값 출력


  delay(2000); //2초 딜레이 
}
