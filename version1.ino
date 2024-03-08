#include "AFMotor.h"
AF_DCMotor motor1(1); // création de l'objet "motor1" - moteurs du coté droit
AF_DCMotor motor2(2); // création de l'objet "motor2" - moteurs du coté gauche


const int EchoR_PIN = 34;
const int EchoM_PIN = 35;
const int EchoL_PIN = 44;

const int TrigR_PIN = 32;
const int TrigM_PIN = 33;
const int TrigL_PIN = 42;

const int VITESSE = 225;
const int SEUIL_DISTANCE = 20;
const int SEUIL_DISTANCE_L = 20;

float distanceR;
float distanceL;
float distanceM;

void release(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void brake(){
  motor1.run(BRAKE);
  motor2.run(BRAKE);
}

void forward(){
  release();
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor1.setSpeed(VITESSE); //max 255
  motor2.setSpeed(VITESSE);
}

void backward(){
  release();
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor1.setSpeed(VITESSE); //max 255
  motor2.setSpeed(VITESSE);
}

void turnLeft(){
  release();
  motor1.run(BACKWARD);
  motor2.run(BRAKE);
  // motor2.run(FORWARD);
  motor1.setSpeed(VITESSE); //max 255
  // motor2.setSpeed(VITESSE);
}

void turnRight(){
  release();
  motor1.run(BRAKE);
  // motor1.run(FORWARD);
  motor2.run(BACKWARD);
  // motor1.setSpeed(VITESSE); //max 255
  motor2.setSpeed(VITESSE);
}

void getSignal(int triggerPin){
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
}

void setup(){
  // put your setup code here, to run once:
  pinMode(EchoM_PIN, INPUT);
  pinMode(TrigM_PIN, OUTPUT);
  pinMode(EchoR_PIN, INPUT);
  pinMode(TrigR_PIN, OUTPUT);
  pinMode(EchoL_PIN, INPUT);
  pinMode(TrigL_PIN, OUTPUT);
  // Serial.begin(115200);
}

void loop(){
  // put your main code here, to run repeatedly:
  getSignal(TrigR_PIN);
  distanceR = (pulseIn(EchoR_PIN, HIGH))/29.0/2.0;
  
  getSignal(TrigL_PIN);
  distanceL = (pulseIn(EchoL_PIN, HIGH))/29.0/2.0;

  getSignal(TrigM_PIN);
  distanceM = (pulseIn(EchoM_PIN, HIGH))/29.0/2.0;

  // getSignal(TrigB_PIN);
  // distanceB = (pulseIn(EchoB_PIN, HIGH))/29.0/2.0;
  if(distanceM < SEUIL_DISTANCE){ //tourner à droite si mur en face
    if(distanceL < distanceR){
      turnRight();
    }else{
      turnLeft();
    }
  }
  if((distanceR < SEUIL_DISTANCE)&&(distanceL < SEUIL_DISTANCE_L)&&(distanceM < SEUIL_DISTANCE)){ //arret
    release();
  }
  if((distanceR < SEUIL_DISTANCE)&&(distanceL > SEUIL_DISTANCE_L)){ //tourner à gauche
    turnLeft();
  }
  if((distanceL < SEUIL_DISTANCE_L)&&(distanceR > SEUIL_DISTANCE)){ //tourner à droite
    turnRight();
  }
  if((distanceR > SEUIL_DISTANCE)&&(distanceL > SEUIL_DISTANCE_L)&&(distanceM > SEUIL_DISTANCE)){ //avancer
    forward();
  }
}
