// MechaMaven: The Educational Robot Explorer, an Open-Source Programmable Smart Robot Car!
// Evtech | @earldanielph | Earl Daniel Villanueva
// beacons.page/evtech

#include <Ps3Controller.h>

#define AIN1_PIN 2
#define AIN2_PIN 4
#define BIN1_PIN 5
#define BIN2_PIN 23
#define CIN1_PIN 32
#define CIN2_PIN 27
#define DIN1_PIN 18
#define DIN2_PIN 19

int rightX = 0;
int rightY = 0;
int leftX = 0;

void notify() {
  rightX = Ps3.data.analog.stick.rx;
  rightY = Ps3.data.analog.stick.ry;
  leftX = Ps3.data.analog.stick.lx;

  int speedX = map(rightX, -128, 127, -255, 255);
  int speedY = map(rightY, -128, 127, -255, 255);
  int rotation = map(leftX, -128, 127, -255, 255);

  int frontLeft = speedY - speedX + rotation;
  int frontRight = speedY + speedX - rotation;
  int backLeft = speedY + speedX + rotation;
  int backRight = speedY - speedX - rotation;

  analogWrite(AIN1_PIN, frontLeft > 0 ? frontLeft : 0);
  analogWrite(AIN2_PIN, frontLeft < 0 ? -frontLeft : 0);

  analogWrite(BIN1_PIN, frontRight > 0 ? frontRight : 0);
  analogWrite(BIN2_PIN, frontRight < 0 ? -frontRight : 0);

  analogWrite(CIN1_PIN, backLeft > 0 ? backLeft : 0);
  analogWrite(CIN2_PIN, backLeft < 0 ? -backLeft : 0);

  analogWrite(DIN1_PIN, backRight > 0 ? backRight : 0);
  analogWrite(DIN2_PIN, backRight < 0 ? -backRight : 0);

  Serial.print("RightX = ");
  Serial.print(rightX);
  Serial.print(" - RightY = ");
  Serial.print(rightY);
  Serial.print(" - LeftX = ");
  Serial.print(leftX);
  Serial.print(" - FL = ");
  Serial.print(frontLeft);
  Serial.print(" - FR = ");
  Serial.print(frontRight);
  Serial.print(" - BL = ");
  Serial.print(backLeft);
  Serial.print(" - BR = ");
  Serial.print(backRight);
  Serial.println();
}

void onConnect() {
  Serial.println("Connected.");
}

void setup() {
  Serial.begin(115200);

  Ps3.attach(notify);
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("58:96:1d:ce:38:cf");

  pinMode(AIN1_PIN, OUTPUT);
  pinMode(AIN2_PIN, OUTPUT);
  pinMode(BIN1_PIN, OUTPUT);
  pinMode(BIN2_PIN, OUTPUT);
  pinMode(CIN1_PIN, OUTPUT);
  pinMode(CIN2_PIN, OUTPUT);
  pinMode(DIN1_PIN, OUTPUT);
  pinMode(DIN2_PIN, OUTPUT);

  Serial.println("Ready.");
}

void loop() {
  if (!Ps3.isConnected())
    return;
  delay(20);
}

// MechaMaven: The Educational Robot Explorer, an Open-Source Programmable Smart Robot Car!
// Evtech | @earldanielph | Earl Daniel Villanueva
// beacons.page/evtech