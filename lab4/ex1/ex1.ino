void setup ()
{
  pinMode(4,OUTPUT); 
  pinMode(7,OUTPUT); 
  pinMode(8,OUTPUT); 
}

byte arr[] = {3, 243, 37, 97, 209, 73, 9, 227, 1, 65};
 
void loop()
{
  for(int i = 0; i < 10 ; i++)
  {
    afiseazaValoareInvers(arr[i], 143);
    delay(1000);
  } 
}
 
void afiseazaValoareInvers(byte valoare, byte segment)
{
  digitalWrite(4,LOW);
  shiftOut(8, 7, LSBFIRST, valoare);
  shiftOut(8, 7, LSBFIRST, segment);
  digitalWrite(4,HIGH);
}