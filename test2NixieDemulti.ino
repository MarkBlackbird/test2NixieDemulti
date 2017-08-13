int usedPins[] = {5,6,7,8,9,10,11,12};
byte value = 0;
const byte WEPin = 0, ZPin = 1, interruptPin = 2, EPin = 3;
bool clockState = LOW;
bool WEState = LOW;
int cnt = 0;

void setup() {
  pinMode(WEPin, OUTPUT);
  pinMode(ZPin, OUTPUT);
  pinMode(interruptPin, INPUT);
  pinMode(EPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt, RISING);
  for(int i=0; i<16; i++)
  {
    pinMode(usedPins[i],OUTPUT);
  }
}
void demultiplex (byte b)
{
  for(int i=0; i<8; i++)
  {
    digitalWrite(usedPins[i],  ((b >> i)  & 0x01));
  }
}
byte clamp (byte b)
{
  byte outbyte = 0;
  outbyte = ((b/10)%10)*16+b%10;
  return outbyte;
}
void interrupt ()
{
  value++;
  digitalWrite(EPin, HIGH);
  demultiplex(clamp(value));
  digitalWrite(EPin, LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
  delay(1);
  clockState=!clockState;
  digitalWrite(ZPin, clockState);
  cnt++;
  if(cnt>1000)
  {
    cnt=0;
    digitalWrite(WEPin, WEState);
    WEState=!WEState;
  }
}
