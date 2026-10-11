 int pin = 7;
int value = 0;

unsigned long totalTime = 1000;
bool state = LOW;

unsigned long lastTime = 0;

int fadeStep = 1;
unsigned long lastFadeTime = 0;
const unsigned long fadeInterval = 30;

void setup() {
  pinMode(pin, OUTPUT);
}

void loop() {
  
  unsigned long currentMillis = millis();
  if (currentMillis - lastFadeTime >= fadeInterval) {
    lastFadeTime = currentMillis;

    value += fadeStep;

    if (value <= 0 || value >= 255) {
      fadeStep = -fadeStep;
    }
  }

  unsigned long currentTime = micros();

  unsigned long time1 = totalTime * value / 255;
  unsigned long time0 = totalTime - time1;
  
  if(state == HIGH)
  {
    if(currentTime - lastTime >= time1)
    {
      if(value < 255)
      {
        digitalWrite(pin, LOW);
        state = LOW;
      }
      lastTime = currentTime;
    }
  }
  else
  {
    if(currentTime - lastTime >= time0)
    {
      if(value > 0)
      {
        digitalWrite(pin, HIGH);
        state = HIGH;
      }
      lastTime = currentTime;
    }
  }
}
