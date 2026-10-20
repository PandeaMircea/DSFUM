unsigned long lastMillis[14] = {0};
unsigned long lastMicros[14] = {0};
bool ledState[14] = {LOW};
unsigned long stepInterval[14] = {0};
int fadeDirection[14] = {1};

void setup() {
  for(int i = 8; i < 14; i++) pinMode(i, OUTPUT);
  Serial.begin(9600);
}

void execute(int led, String animation, unsigned long time)
{
  if(led == -1) return;
  if(animation == "") return;
  if(time == 0) return;

  if (animation == "fadeIn") fadeIn(led, time);
  else if (animation == "fadeOut") fadeOut(led, time);
  else if (animation == "fadeInOut") fadeInOut(led, time);
  else if (animation == "blink") blink(led, time);
  else if (animation == "off") off(led, time);
}

int leds[6] = {8, 9, 10, 11, 12, 13};
String animations[14];
unsigned long times[14] = {0};
int brightness[14] = {0};
int fadeAmount[14] = {0};

void aplicaBrightness(int led, int val)
{
  if(led == 9 || led == 10 || led == 11) analogWrite(led, val);
  else
  {
    unsigned long currentMicros = micros();
    unsigned long totalPeriod = 2000;
    
    unsigned long time1 = totalPeriod * val / 255;
    unsigned long time0 = totalPeriod - time1;
    
    if(ledState[led] == HIGH)
    {
      if(currentMicros - lastMicros[led] >= time1)
      {
        if(val < 255)
        {
          digitalWrite(led, LOW);
          ledState[led] = LOW;
        }
        lastMicros[led] = currentMicros;
      }
    }
    else
    {
      if(currentMicros - lastMicros[led] >= time0)
      {
        if(val > 0)
        {
          digitalWrite(led, HIGH);
          ledState[led] = HIGH;
        }
        lastMicros[led] = currentMicros;
      }
    }
  }
}

void fadeIn(int led, unsigned long time)
{
  unsigned long currentMillis = millis();
  unsigned long interval = stepInterval[led];
  if(interval == 0) interval = 1;

  if(currentMillis - lastMillis[led] >= interval)
  {
    lastMillis[led] = currentMillis;
    brightness[led]++;
    if(brightness[led] > 255) brightness[led] = 0;
  }
  aplicaBrightness(led, brightness[led]);
}

void fadeOut(int led, unsigned long time)
{
  unsigned long currentMillis = millis();
  unsigned long interval = stepInterval[led];
  if(interval == 0) interval = 1;

  if(currentMillis - lastMillis[led] >= interval)
  {
    lastMillis[led] = currentMillis;
    brightness[led]--;
    if(brightness[led] < 0) brightness[led] = 255;
  }
  aplicaBrightness(led, brightness[led]);
}

void fadeInOut(int led, unsigned long time)
{
  unsigned long currentMillis = millis();
  unsigned long interval = stepInterval[led];
  if(interval == 0) interval = 1;

  if(currentMillis - lastMillis[led] >= interval)
  {
    lastMillis[led] = currentMillis;
    brightness[led] += fadeDirection[led];
    if(brightness[led] >= 255 || brightness[led] <= 0)
    {
      fadeDirection[led] = -fadeDirection[led];
    }
  }
  aplicaBrightness(led, brightness[led]);
}

void blink(int led, unsigned long time)
{
  unsigned long currentMillis = millis();
  unsigned long interval = time / 2;
  if(interval == 0) interval = 1;

  if(currentMillis - lastMillis[led] >= interval)
  {
    lastMillis[led] = currentMillis;
    if(brightness[led] == 0) brightness[led] = 255;
    else brightness[led] = 0;
  }
  aplicaBrightness(led, brightness[led]);
}

void off(int led, unsigned long time)
{
  brightness[led] = 0;
  aplicaBrightness(led, 0);
}

void loop() 
{
  String params[3];

  if(Serial.available() > 0)
  {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int k = 0;
    for(int i = 0; input[i]; i++)
    {
      if(input[i] == ',') k++;
      else if(input[i] != ' ' ) params[k].concat(input[i]);
    }
  }

  while(Serial.available() > 0) Serial.read();

  int led = params[0].toInt();
  String animation = params[1];
  int time;
  if(params[2].toInt() > 0) time = params[2].toInt();
  else time = 10000; // default

  if(led >= 8 && led <= 13)
    if(animation == "fadeIn" || animation == "fadeOut" || animation == "fadeInOut" || animation == "blink" || animation == "off")
      if(time > 0 )
      {
        animations[led] = animation;
        times[led] = time;
        brightness[led] = 0;
        
        if(animation == "fadeIn") {
          stepInterval[led] = time / 255;
          fadeDirection[led] = 1;
          brightness[led] = 0;
        }
        else if(animation == "fadeOut") {
          stepInterval[led] = time / 255;
          fadeDirection[led] = -1;
          brightness[led] = 255;
        }
        else if(animation == "fadeInOut") {
          stepInterval[led] = time / 510;
          fadeDirection[led] = 1;
          brightness[led] = 0;
        }
        else if(animation == "blink") {
          stepInterval[led] = time / 2;
        }

        Serial.write(led);
        Serial.write(time);
      }
  
  for(int i = 0 ; i < 6; i++) 
  {
    execute(leds[i], animations[leds[i]], times[leds[i]]);
  }
}