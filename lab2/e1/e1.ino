void setup() {
    for(byte i=8; i<=13; i++)
        pinMode(i, OUTPUT);
}

void loop() {
    for(int i = 8; i <= 13; i++) digitalWrite(i, 0);

    for(int i = 0; i < 64; i++)
    {
      int x = i;
      for(int j = 8; j <= 13 && x; j++)
      {
          digitalWrite(j, x % 2);
          x /= 2;
      }
      delay(500);
    }
}