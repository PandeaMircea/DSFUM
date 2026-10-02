int last = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  if (Serial.available()>0)
  {
    int sentByte = Serial.parseInt();

    if(sentByte == 1)
    {
        last = 1;
        Serial.println("pornit");
        digitalWrite(13, 1);
    }
    else if(sentByte == 2 && last != 2)
    {
        last = 2;
        Serial.println("oprit");
        digitalWrite(13, 0);
    }
    else if(sentByte == 3)
    {   
        last = 3;
        Serial.println("blink");
        digitalWrite(13, 1);  
        delay(1000);                      
        digitalWrite(13, 0);    
        delay(1000);  
    }
  }
  else if(last == 3)
  {
      digitalWrite(13, 1);  
      delay(1000);                      
      digitalWrite(13, 0);    
      delay(1000);  
  }
}
