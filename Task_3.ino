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

int ls_value; //left sensor value

int i; //counter

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(1000);
  servo.attach(7);
  servo.write(90);
}

void loop(){
  distance=sr04.Distance();
  Serial.println(distance);
  if(distance < 6) //detects an obstacle in 10cm (arbitrary distance, should be ~L)
  {
    Serial.println("Osbtacle Detected");
    obstacle();
  }
  servo.write(90);
  stepper.step(-300);
  
}

void obstacle(){
  Serial.println("Deciding Direction");
  servo.write(180); //turn driver wheel right
  delay(1000);
  rs_value = sr04.Distance(); //read right value
  Serial.print("Right Value: ");
  Serial.println(rs_value);
  delay(1000); 
  servo.write(0); //turn driver wheel left
  delay(1000); 
  ls_value = sr04.Distance(); //read left value
  Serial.print("Left Value: ");
  Serial.println(ls_value);
  delay(1000);
  servo.write(90);
  delay(1000);

  if(rs_value > ls_value)
  {
    Serial.print("Right");
    right_obstacle();
  }
  else if(ls_value > rs_value)
  {
    Serial.print("Left");
    left_obstacle();
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
  
}

void left()
{
  Serial.println("Turning Left");
  servo.write(0); //turn driver wheel left
  delay(500);
  stepper.step(-3500); //rotate left
  delay(1500);//arbitrary time alotted for rotation
  servo.write(90);
  stepper.step(-2000);
}

void right_obstacle()
{
  right();
  do
  {
    servo.write(90);
    stepper.step(-2500);
    delay(1000); 
    servo.write(0); //turn driver wheel left
    delay(1000); 
    ls_value = sr04.Distance(); //read left value
    i++;
  }while(ls_value < 10);
  //left();
//  do
//  {
//    servo.write(90);
//    stepper.step(-2048);
//    delay(1000); 
//    servo.write(0); //turn driver wheel left
//    delay(1000); 
//    ls_value = sr04.Distance(); //read left value
//  }while(ls_value < 10);
//  servo.write(90);
//  stepper.step(-2500);
  left();
  stepper.step(-4000);
  delay(1000);
  left();
  stepper.step(-2000);
  delay(1000);
  right();
//  servo.write(90);
//  stepper.step(-2500*i);
//  right();
//  stepper.step(-2048);
//  i = 0;
}

void left_obstacle()
{
  left();
  do
  {
    servo.write(90);
    stepper.step(-2500);
    delay(1000); 
    servo.write(180); //turn driver wheel right
    delay(1000); 
    rs_value = sr04.Distance(); //read right value
    i++;
  }while(rs_value < 10);
  right();
  do
  {
    servo.write(90);
    stepper.step(-2048);
    delay(1000); 
    servo.write(180); //turn driver wheel right
    delay(1000); 
    rs_value = sr04.Distance(); //read right value
  }while(rs_value < 10);
  servo.write(90);
  stepper.step(-2500);
  right();
  servo.write(90);
  stepper.step(-2048*i);
  left();
  stepper.step(-2048);
  i = 0;
}
