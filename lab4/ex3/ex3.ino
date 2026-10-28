byte digitsMSB[] = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144}; 
int posArr[] = {241, 242, 244, 248};

int counter = 0;

bool lastA1 = LOW;
bool lastA2 = LOW;
bool lastA3 = LOW;

void setup() {
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void loop() {
  checkButtons();

  int m = counter / 1000;
  int s = (counter / 100) % 10;
  int z = (counter / 10) % 10;
  int u = counter % 10;

  byte m_val = (counter >= 1000) ? digitsMSB[m] : 255;
  byte s_val = (counter >= 100) ? digitsMSB[s] : 255;
  byte z_val = (counter >= 10) ? digitsMSB[z] : 255;
  byte u_val = digitsMSB[u];

  byte displayValues[] = {m_val, s_val, z_val, u_val};

  for (int i = 0; i < 4; i++) 
  {
    digitalWrite(4, LOW);
    shiftOut(8, 7, MSBFIRST, displayValues[i]);
    shiftOut(8, 7, MSBFIRST, posArr[i]);
    digitalWrite(4, HIGH);
    
    delay(2);
  }
}

void checkButtons() 
{
  bool currentA1 = digitalRead(A1);
  bool currentA2 = digitalRead(A2);
  bool currentA3 = digitalRead(A3);

  if (currentA1 == HIGH && lastA1 == LOW) 
  {
    if (counter < 9999) counter++;
    delay(30);
  }

  if (currentA2 == HIGH && lastA2 == LOW) 
  {
    if (counter > 0) counter--;
    delay(30);
  }

  if (currentA3 == HIGH && lastA3 == LOW) 
  {
    counter = 0;
    delay(30);
  }

  lastA1 = currentA1;
  lastA2 = currentA2;
  lastA3 = currentA3;
}