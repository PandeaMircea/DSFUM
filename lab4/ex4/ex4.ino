void setup ()
{
  pinMode(4,OUTPUT); 
  pinMode(7,OUTPUT); 
  pinMode(8,OUTPUT); 
}

byte arrLSB[] = {17, 193, 99, 133, 97, 113};
 
void loop()
{
  for(int i = 0; i < 6; i++)
  {
    afiseazaValoare(arrLSB[i], 143);
    delay(5000);
  } 
}
 
void afiseazaValoare(byte valoare, byte segment)
{
  digitalWrite(4,LOW);
  shiftOut(8, 7, LSBFIRST, valoare);
  shiftOut(8, 7, LSBFIRST, segment);
  digitalWrite(4,HIGH);
}