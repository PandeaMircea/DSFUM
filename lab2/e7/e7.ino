int leds[6] = {8, 9, 10, 11, 12, 13};
int brightness[6] = {0, 0, 0, 0, 0, 0};
int fadeAmount[6] = {2, 4, 6, 8, 10, 12};

void setup() {
  for(int i = 0; i < 6; i++) pinMode(leds[i], OUTPUT);
}

void loop() {
  for(int i = 0; i < 6; i++) 
  {
    analogWrite(leds[i], brightness[i]);

    brightness[i] = brightness[i] + fadeAmount[i];

    if (brightness[i] <= 0 || brightness[i] >= 255) fadeAmount[i] = -fadeAmount[i];

  }
  delay(10);
}
