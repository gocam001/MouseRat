#ifndef MR_IR_h
#define MR_IR_h

#include <Arduino.h>

#define receiverL A8
#define emitterL 23

#define receiverML A5
#define emitterML 18

#define receiverM A2
#define emitterM 17

#define receiverMR A0
#define emitterMR 15

#define receiverR A6
#define emitterR 21

int sensorReadingL = 0;
int sensorReadingML = 0;
int sensorReadingM = 0;
int sensorReadingMR = 0;
int sensorReadingR = 0;

void onIR() {
    
    digitalWrite(emitterL, HIGH);
    digitalWrite(emitterML, HIGH);
    digitalWrite(emitterM, HIGH);
    digitalWrite(emitterMR, HIGH);
    digitalWrite(emitterR, HIGH);
    
}

void offIR() {
    
    digitalWrite(emitterL, LOW);
    digitalWrite(emitterML, LOW);
    digitalWrite(emitterM, LOW);
    digitalWrite(emitterMR, LOW);
    digitalWrite(emitterR, LOW);

}

void getIR() {
    
    sensorReadingL = analogRead(receiverL);
    sensorReadingML = analogRead(receiverML);
    sensorReadingM = analogRead(receiverM);
    sensorReadingMR = analogRead(receiverMR);
    sensorReadingR = analogRead(receiverR);
    
}

#endif
