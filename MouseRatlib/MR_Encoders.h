#ifndef MR_Encoders_h
#define MR_Encoders_h

#include <Arduino.h>

#define encoderLA 2
#define encoderLB 1
#define encoderRA 12
#define encoderRB 11

/* Header file implementations for MouseRat's Encoders */

volatile long tickLA = 0;
volatile long tickLB = 0;
volatile long tickRA = 0;
volatile long tickRB = 0;


//Interrupt ISRs
void leftTickA() {
    tickLA++;
}

void leftTickB() {
    tickLB++;
}

void rightTickA() {
    tickRA++;
}

void rightTickB() {
    tickRB++;
}

#endif
