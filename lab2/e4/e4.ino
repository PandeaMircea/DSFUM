/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Fade/
*/

int led = 9;         // the PWM pin the LED is attached to
int brightness = 0;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by

unsigned long prevMillis = 0;
int interval = 30;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

char c;
int x = 0;

void loop() {
  while (Serial.available() > 0)
  {
    c = Serial.read();
    if (c == '\n') {
      if (x > 0) {
        interval = x;
      }
      x = 0;
      break;
    }
    x*= 10;
    x += c - '0';
  }

  unsigned long currentMillis = millis();
  
  if (currentMillis - prevMillis >= interval) {
    prevMillis = currentMillis; 

    analogWrite(led, brightness);

    brightness = brightness + fadeAmount;

    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
  }
}
