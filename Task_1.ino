#include "Stepper.h"
#define STEPS  32 
#include <Servo.h>
Servo myservo;

Stepper small_stepper(STEPS, 8, 10, 9, 11);

const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
int a=90;
int pace=1000;
int deg;
int y=analogRead(Y_pin);
int x=analogRead(X_pin);

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
  myservo.attach(7);
  myservo.write(90);
  small_stepper.setSpeed(pace);
}

void loop() 
{
//  Serial.print("Switch:  ");
//  Serial.print(digitalRead(SW_pin));
//  Serial.print("\n");
//  Serial.print("X-axis: ");
//  Serial.print(analogRead(X_pin));
//  Serial.print("\n");
//  Serial.print("Y-axis: ");
//  Serial.println(analogRead(Y_pin));
//  Serial.print("\n\n");
//  delay(1000);

  if (analogRead(X_pin)<450 * analogRead(Y_pin)>200)//up
  {
   //pace=(-1.25)*analogRead(X_pin)+500; 
   small_stepper.setSpeed(pace);
   small_stepper.step(+256);
   
  }
//   if (analogRead(X_pin)<200)//up
//  {
//  //pace=(-1.25)*analogRead(X_pin)+500;
////   small_stepper.setSpeed(pace);
////   small_stepper.step(+256);
//   
//  }
  if (analogRead(X_pin) > 800) //down
  {
   //pace=analogRead(X_pin)/2; 
   small_stepper.setSpeed(pace);
   small_stepper.step(-256);
  }
//  if (analogRead(X_pin)>515 && analogRead(X_pin)<800)//down
//  {
//   //pace=analogRead(X_pin)/2; 
//   small_stepper.setSpeed(pace);
//   small_stepper.step(-256);
//  }
  if (analogRead(Y_pin)<400)//right
  {
   deg=analogRead(Y_pin)/5.68;
   myservo.write(deg);
    
  }
  if (analogRead(Y_pin)>515) //left
  {
   deg=analogRead(Y_pin)/5.68;
   myservo.write(deg);
  }
}
