#ifndef MR_Motors_h
#define MR_Motors_h

#define FULL_SPEED 255

#include <Arduino.h>

#define motorENL 0
#define motorENR 13

#define motorLogicL1 3
#define motorLogicL2 4

#define motorLogicR1 9
#define motorLogicR2 10

void forward(int spdL, int spdR) {
    //LEFT
    digitalWrite(motorENL, HIGH);
    analogWrite(motorLogicL1, 0);
    analogWrite(motorLogicL2, spdL);
    
    //RIGHT
    digitalWrite(motorENR, HIGH);
    analogWrite(motorLogicR1, spdR);
    analogWrite(motorLogicR2, 0);
}

void reverse() {
    
    //LEFT
    digitalWrite(motorENL, HIGH);
    analogWrite(motorLogicL1, HIGH);
    analogWrite(motorLogicL2, LOW);
    
    //RIGHT
    digitalWrite(motorENR, HIGH);
    analogWrite(motorLogicR1, LOW);
    analogWrite(motorLogicR2, HIGH);
}

void breakMotors() {
    //RIGHT
    digitalWrite(motorENR, HIGH);
    analogWrite(motorLogicR1, HIGH);
    analogWrite(motorLogicR2, HIGH);
    
    //LEFT
    digitalWrite(motorENL, HIGH);
    analogWrite(motorLogicL1, HIGH);
    analogWrite(motorLogicL2, HIGH);
}

#endif
