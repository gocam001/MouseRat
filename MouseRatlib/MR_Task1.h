#ifndef MR_Task1_h
#define MR_Task1_h

#include <MR_Motors.h>

enum FWDStates {INIT, FWD} FWD_State;

void FWD_Init() {
    
    FWD_State = INIT;
    
    pinMode(motorENL, OUTPUT);
    pinMode(motorLogicL1, OUTPUT);
    pinMode(motorLogicL2, OUTPUT);
    digitalWrite(motorENL, LOW);
    
    pinMode(motorENR, OUTPUT);
    pinMode(motorLogicR1, OUTPUT);
    pinMode(motorLogicR2, OUTPUT);
    digitalWrite(motorENR, LOW);
}

void FWD_Tick() {
    
    //Actions
    switch(FWD_State) {
        case INIT:
            break;
        case FWD:
            forward(255, 255);
            break;
        default:
            break;
    }
    
    //Transitions
    switch(FWD_State) {
        case INIT:
            FWD_State = FWD;
            break;
        case FWD:
            FWD_State = FWD;
            break;
        default:
            break;
    }
}

#endif
