#include <Arduino.h>

int WorkFlag = 0;
int FlagStan = 0;
float Pause = 0;
float TimerPau = 0;
float TimerPusk = 0;
int PuskPin = 13;
int ButtonPin = 8;
int ButFlag = 0;
float ButTimer = 0;
bool Buton = false;
bool ButonFilt = false;
int RedLed = 5;
int BlueLed = 6;
float WorkTimer = 0;

void Pusk()
{

  TimerPusk = millis();
  while (millis() - TimerPusk < 800.0)
  {
    digitalWrite(PuskPin, HIGH);
  }
  digitalWrite(PuskPin, LOW);
}

void Worked()
{
  if (WorkFlag == 0)
  {
    WorkTimer = millis();
    WorkFlag = 1;
  }
  if (WorkFlag == 1 && millis() - WorkTimer > Pause)
  {
    Pusk();
    WorkFlag = 0;
  }
}

void GetPause()
{
  if (ButonFilt && FlagStan == 0)
  {
    Pusk();
    TimerPau = millis();
    ButonFilt = false;
    FlagStan = 1;
  }
  if (ButonFilt && FlagStan == 1)
  {
    Pusk();
    Pause = millis() - TimerPau;
    ButonFilt = false;
    FlagStan = 2;
  }
  if (ButonFilt && FlagStan == 2)
  {
    Pause = 0;
    ButonFilt = false;
    FlagStan = 0;
  }
  if (FlagStan == 1 && millis() - TimerPau > 60000.0)
  {
    FlagStan = 0;
  }
}

void GetBut()
{
  Buton = digitalRead(ButtonPin);
  if (Buton == 0 && ButFlag == 0)
  {
    ButTimer = millis();
  }
  if (Buton == 1 && ButFlag == 0 && millis() - ButTimer > 100)
  {
    ButonFilt = true;
    ButFlag = 1;
  }
  if (ButFlag == 1 && millis() - ButTimer > 200)
  {
    ButonFilt = false;
    ButFlag = 2;
  }
  if (Buton == 0 && ButFlag == 2 && millis() - ButTimer > 1000)
  {
    ButFlag = 0;
  }
}

void setup()
{

 // Serial.begin(9600);
  pinMode(PuskPin, OUTPUT);
  pinMode(RedLed, OUTPUT);
  pinMode(BlueLed, OUTPUT);
  pinMode(ButtonPin, INPUT);
}

void loop()
{
 // Serial.print("BlueLed= ");
 // Serial.println(digitalRead(BlueLed));
 // Serial.print("          RedLed= ");
  //Serial.println(digitalRead(RedLed));         //Diagnostic block
  //Serial.print("                   Pause= ");
 // Serial.println(Pause);

  GetBut();
  GetPause();

  if (Pause != 0)
  {
    Worked();
    digitalWrite(BlueLed, HIGH);
  }
  else
  {
    digitalWrite(BlueLed, LOW);
  }

  if (FlagStan == 1)
  {
    digitalWrite(RedLed, HIGH);
  }
  else
  {
    digitalWrite(RedLed, LOW);
  }
}
