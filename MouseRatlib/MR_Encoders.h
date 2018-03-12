#ifndef MR_Encoders_h
#define MR_Encoders_h

#include <Arduino.h>

#define encoderLA 2
#define encoderRA 12

/* Header file implementations for MouseRat's Encoders */

extern volatile long tickLA = 0;
extern volatile long tickRA = 0;


//Interrupt ISRs
void leftTick() {
    tickLA++;
}

void rightTick() {
    tickRA++;
}

#endif
