#include "Stepper.h"
#define STEPS  32 
#include <Servo.h>
#include <SR04.h>
#define TRIG_PIN 5
#define ECHO_PIN 3 

Servo servo;
Stepper stepper(STEPS, 8, 10, 9, 11);
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

int distance;

int rs_value; //right sensor value

int ls_value; //left sensor value\

int i=0;

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(1000);
  servo.attach(7);
  servo.write(90);
}

void loop(){
  distance=sr04.Distance();
  Serial.println(distance);
  if(distance < 10) //detects an obstacle in 10cm (arbitrary distance, should be ~L)
  {
    Serial.println("Osbtacle Detected");
    obstacle();
  }
  stepper.step(-300);
  servo.write(90);
}

void obstacle(){
  Serial.println("Deciding Direction");
  servo.write(180); //turn driver wheel right
  delay(1000);
  rs_value = sr04.Distance(); //read right value
  Serial.println("Rs Value:");
  Serial.println(rs_value);
  delay(1000); 
  servo.write(0); //turn driver wheel left
  delay(1000);
  ls_value = sr04.Distance(); //read left value
        Serial.println("Ls Value:");
        Serial.println(ls_value);
  delay(1000);
  servo.write(90);
  delay(1000);
  while(i>1)
  {
    stepper.step(0);
  }
  
  if(rs_value < ls_value)
  {
    left();
  }
  else if(ls_value < rs_value)
  {
    right();
  }
}

void right()
{
  Serial.println("Turning Right");
  servo.write(180); //turn driver wheel right
  delay(500);
  stepper.step(-4500); //rotate right
  delay(1500);//arbitrary time alotted for rotation
  servo.write(90);
  i++;
  
}

void left()
{
  Serial.println("Turning Left");
  servo.write(0); //turn driver wheel left
  delay(500);
  stepper.step(-3500); //rotate left
  delay(1500);//arbitrary time alotted for rotation
  servo.write(90);
  i++;
}
