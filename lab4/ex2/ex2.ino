void setup ()
{
  pinMode(4,OUTPUT); 
  pinMode(7,OUTPUT); 
  pinMode(8,OUTPUT); 
  Serial.begin(9600);
}

bool guessing = 0;
int tries = 10;
unsigned long sum = 0;
unsigned long longest = 0;
unsigned long shortest = 999999;

byte digitsLSB[] = {3, 159, 37, 13, 153, 73, 65, 31, 1, 9};
byte digitsMSB[] = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144}; 
 
void loop()
{
  if(tries)
  {
    String number;

    for(int i = 0; i < 4 ; i++)
    {
      int digit = random(0, 10);
      int pos = 240 + pow(2, i);

      number.concat(digit);

      digitalWrite(4,LOW);
      shiftOut(8, 7, MSBFIRST, digitsMSB[digit]);
      shiftOut(8, 7, MSBFIRST, pos);
      digitalWrite(4,HIGH);

      delay(5);
    } 

    unsigned long start = millis();
    unsigned long finish;
    unsigned long time;

    while(1)
    {
      String input;

      if(Serial.available() > 0)
      {
        input = Serial.readStringUntil('\n');
        input.trim();
      }

      while(Serial.available()) Serial.read();

      if(input == number)
      {
        tries--;
        finish = millis();
        time = finish - start;

        if(time > longest) longest = time;
        else if(time < shortest) shortest = time;

        sum += time;

        break;
      }
    }
  }
  else
  {
    Serial.write(shortest);
    Serial.write(longest);
    Serial.write(sum / 10);

    while(1) {};
  }
  
  
}