#include <stdio.h>
#include <stdlib.h>

//defining constants
long int currTime = 0;
int state =0;
int prevState = 0;
long int prevPulseTime;
int prox = 11;
int currState =0;
long int timeStep = 0;
float RPM = 0;
int count= 0;
long int startTime =0;
long int stopTime =0;
int speedtime = 12;
int getSpeed();
double sineFreq = 10.0;
int refRPM = 250;
//binary array: intially zero
boolean Bin[] = {0,0,0,0,0,0,0};
int pin0=2;
int pin1=3;
int pin2=4;
int pin3=6;
int pin4=7;
int pin5=8;
int pin6=9;

int main()
{

 /*
The following function convert any int from 0-128 to binary.
You need to pass the int as agrument.
You also need to pass the 8bit array of boolean
*/
void convertDecToBin(int Dec, boolean Bin[]) {
  for(int i = 6 ; i >= 0 ; i--) {
    if(pow(2, i)<=Dec) {
      Dec = Dec - pow(2, i);
      Bin[7-(i+1)] = 1;
    }
  }
    digitalWrite(pin0, Bin[0]);
    digitalWrite(pin1, Bin[1]);
    digitalWrite(pin2, Bin[2]);
    digitalWrite(pin3, Bin[3]);
    digitalWrite(pin4, Bin[4]);
    digitalWrite(pin5, Bin[5]);
    digitalWrite(pin6, Bin[6]);
}
/*
This following function will convert any 8 bit array of boolean to a Decimal number.
you need to pass an boolean array of 8 bits
function return a int
*/

int convertBinToDec(boolean Bin[]) {
  int ReturnInt = 0;
  for (int i = 0; i < 8; i++) {
    if (Bin[7 - i]) {
      ReturnInt += 1<<i;
    }
  }
  return ReturnInt;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pin0, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
 currTime = micros();
 currState = digitalRead(prox);  //current state

  if (currState == 1 && prevState ==0) {
    timeStep = currTime - prevPulseTime;
    RPM = 60/(timeStep * 0.001* 0.001);
    prevPulseTime = currTime;
  }

  prevState = currState;



  if (currTime < stopTime && currTime > startTime)
     {
      digitalWrite(speedtime,HIGH);
     }

   else
   {

    startTime = currTime;
    stopTime = currTime + RPM;
    digitalWrite(speedtime,LOW);


  }


  if (RPM < refRPM){

    sineFreq = sineFreq + 0.5;
  }
  else if (RPM > refRPM) {
    sineFreq = sineFreq - 0.5;
  }
  else if (RPM == refRPM){
    sineFreq = sineFreq;
  }

  if (sineFreq > 15){
    sineFreq = 15;
  }

  else if (sineFreq < 3){
    sineFreq = 3;
  }
    convertDecToBin(sineFreq,Bin);
}
}
