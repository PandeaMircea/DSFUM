void setup() {
  pinMode(4, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT); 
  Serial.begin(9600);
}

int tries = 10;
unsigned long sum = 0;
unsigned long longest = 0;
unsigned long shortest = 999999;
String minNum = "";
String maxNum = "";

byte digitsMSB[] = {192, 249, 164, 176, 153, 146, 130, 248, 128, 144}; 

void loop() {
  if (tries > 0) {
    int generatedDigits[4];
    String number = "";

    for (int i = 0; i < 4; i++) {
      generatedDigits[i] = (i == 0) ? random(1, 10) : random(0, 10);
      number.concat(generatedDigits[i]);
    }

    unsigned long start = millis();
    String input = "";

    while (true) {
      for (int i = 0; i < 4; i++) {
        int posArr[] = {241, 242, 244, 248};

        digitalWrite(4, LOW);
        shiftOut(8, 7, MSBFIRST, digitsMSB[generatedDigits[i]]);
        shiftOut(8, 7, MSBFIRST, posArr[i]);
        digitalWrite(4, HIGH);
        
        delay(2);
      }

      if (Serial.available() > 0) {
        input = Serial.readStringUntil('\n');
        input.trim();
        if (input == number) {
          unsigned long time = millis() - start;
          tries--;

          if (time < shortest) {
            shortest = time;
            minNum = number;
          }

          if (time > longest) {
            longest = time;
            maxNum = number;
          }

          sum += time;
          break;
        }
      }
    }
  } 
  else {
    Serial.print("Minim: "); Serial.print(shortest); Serial.print(" ms, "); Serial.println(minNum);
    Serial.print("Maxim: "); Serial.print(longest); Serial.print(" ms, "); Serial.println(maxNum);
    Serial.print("Medie: "); Serial.print(sum / 10); Serial.println(" ms");

    while (1) {};
  }
}