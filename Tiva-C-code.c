int pin0=2;
int pin1=3;
int pin2=4;
int pin3=5;
int pin4=6;
int pin5=7;
int pin6=8;
int decimal = 0;
boolean Bin[] = {0,0,0,0,0,0,0};

int convertBinToDec(boolean Bin[]) {
  int ReturnInt = 0;
  for (int i = 0; i < 7; i++) {
    if (Bin[6 - i]) {
      ReturnInt += 1<<i;
    }
  }
  return ReturnInt;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pin0, INPUT);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
  pinMode(pin5, INPUT);
  pinMode(pin6, INPUT);
  Serial.begin(9600);
}

void loop() {
Bin[0]=digitalRead(pin0);
Bin[1]=digitalRead(pin1);
Bin[2]=digitalRead(pin2);
Bin[3]=digitalRead(pin3);
Bin[4]=digitalRead(pin4);
Bin[5]=digitalRead(pin5);
Bin[6]=digitalRead(pin6);
decimal = convertBinToDec(Bin);
Serial.println(decimal);
}
