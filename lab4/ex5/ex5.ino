void setup ()
{
  pinMode(4,OUTPUT); 
  pinMode(7,OUTPUT); 
  pinMode(8,OUTPUT);

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT); 
}

bool lastA1 = HIGH;
bool lastA2 = HIGH;
bool lastA3 = HIGH;

byte arrLSB[] = {17, 193, 99, 133, 97, 113, 239, 227, 159, 135, 3, 49, 73, 131};
//               A    b   C    d   E    F    _    L    i    J   O   P  S    U

byte prop[] = {133, 97, 99, 97, 193, 17, 227, 239,
               73, 159, 239,
               113, 159, 131, 227, 239, 
               73, 17, 131, 239, 
               227, 3, 99, 131, 159, 97, 73, 99, 239, 
               49, 97, 239, 
               49, 227, 17, 159, 131, 227, 239,
               133, 17, 99, 159, 97, 159, 239};

byte posArr[] = {143, 79, 47, 31};

int size = 46;
int pos = 0;

bool running = 1;
 
void loop()
{
  unsigned long start = millis();
  
  while(millis() - start < 500)
  {
    checkButtons();
    for(int i = 0; i < 4; i++)
    {
      afiseazaValoare(prop[(pos + i) % size], posArr[i]);
      delay(2);
    } 
  }

  if(running) pos = (pos + 1) % size;
}
 
void afiseazaValoare(byte valoare, byte segment)
{
  digitalWrite(4,LOW);
  shiftOut(8, 7, LSBFIRST, valoare);
  shiftOut(8, 7, LSBFIRST, segment);
  digitalWrite(4,HIGH);
}

void checkButtons() 
{
  bool currentA1 = digitalRead(A1);
  bool currentA2 = digitalRead(A2);
  bool currentA3 = digitalRead(A3);

  if (currentA1 == LOW && lastA1 == HIGH) 
  {
    running = !running;
    delay(5);
  }

  if (currentA2 == LOW && lastA2 == HIGH) 
  {
    running = !running;
    delay(5);
  }

  if (currentA3 == LOW && lastA3 == HIGH) 
  {
    running = !running;
    delay(5);
  }

  lastA1 = currentA1;
  lastA2 = currentA2;
  lastA3 = currentA3;
}