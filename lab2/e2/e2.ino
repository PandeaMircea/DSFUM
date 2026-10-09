void setup() {
  Serial.begin(9600);
  for(byte i=8; i<=13; i++)
        pinMode(i, OUTPUT);
}

void loop() {
  if(Serial.available() > 0)
  {

    int input = Serial.parseInt();
    int x = input % 64;

    while (Serial.parseInt() > 0) Serial.read();

    for(byte i=8; i<=13; i++) digitalWrite(i, 0);

    for(int j = 8; j <= 13 && x; j++)
      {
          digitalWrite(j, x % 2);
          x /= 2;
      }
  }
}
