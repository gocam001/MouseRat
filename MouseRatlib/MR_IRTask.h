#ifndef MR_IRTask_h 
#define MR_IRTask_h

#include <MR_IR.h>

enum getIRStates {INIT_5, ON, OFF} getIR_States;

void getIR_Init() {
    
    pinMode(receiverL, INPUT);
    pinMode(emitterL, OUTPUT);
    pinMode(receiverML, INPUT);
    pinMode(emitterML, OUTPUT);
    pinMode(receiverM, INPUT);
    pinMode(emitterM, OUTPUT);
    pinMode(receiverMR, INPUT);
    pinMode(emitterMR, OUTPUT);
    pinMode(receiverR, INPUT);
    pinMode(emitterR, OUTPUT);
    
    getIR_States = INIT_5;
}

void getIR_Tick() {
    
    //Actions
    switch(getSpeed_State) {
        case INIT_5:
            break;
        case ON:
            break;
        default:
            break;
    }
    
    //Transitions
    switch(getSpeed_State) {
        case INIT_5:
            getSpeed_State = SAMPLE;
            break;
        case SAMPLE:
            getSpeed_State = SAMPLE;
            break;
        default:
            break;
    }
}

#endif
