#ifndef MR_PID_h
#define MR_PID_h

#include <MR_Motors.h>
#include <MR_Encoders.h>

#define RFULL_SPEED 255
#define LFULL_SPEED 255

int rSpeed = 0;
int lSpeed = 0;
int speedAdjustL = 0;
int speedAdjustR = 0;
int distance = 0;

double Kp = .5;
double Kd = .125;

long totalTickL = 0;
long totalTickR = 0;

enum getSpeedStates {INIT_2, SAMPLE} getSpeed_State;
enum ePIDStates {INIT_3, CONTROL } ePID_State;
enum SetStates {INIT_4, SET, STOP} Set_State;

void getSpeed_Init() {
    
    pinMode(motorENL, OUTPUT);
    pinMode(motorLogicL1, OUTPUT);
    pinMode(motorLogicL2, OUTPUT);
    digitalWrite(motorENL, LOW);
    
    pinMode(motorENR, OUTPUT);
    pinMode(motorLogicR1, OUTPUT);
    pinMode(motorLogicR2, OUTPUT);
    digitalWrite(motorENR, LOW);
    
    attachInterrupt(digitalPinToInterrupt(encoderLA), leftTickA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderLB), leftTickB, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderRA), rightTickA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderRB), rightTickB,CHANGE);
    
    getSpeed_State = INIT_2;
}

void getSpeed_Tick() {
    static long rightVal = 0;
    static long leftVal = 0;
    //Actions
    
    switch(getSpeed_State) {
        case INIT_2:
            break;
        case SAMPLE:
            totalTickL = tickLA + tickLB;
            totalTickR = tickRA + tickRB;
            rSpeed = totalTickR - rightVal;
            lSpeed = totalTickL - leftVal;
            rightVal = totalTickR;
            leftVal = totalTickL;
            break;
        default:
            break;
    }
    
    //Transitions
    switch(getSpeed_State) {
        case INIT_2:
            getSpeed_State = SAMPLE;
            break;
        case SAMPLE:
            getSpeed_State = SAMPLE;
            break;
        default:
            break;
    }

}

void ePID_Init() {
    ePID_State = INIT_3;
}

void ePID_Tick() {
    int newError = 0;
    int oldError = 0;
    int totalError = 0;
    int p = 0;
    int d = 0;
    //Actions
    switch(ePID_State) {
        case INIT_3:
            break;
        case CONTROL:
            if (lSpeed < rSpeed) {
                newError = rSpeed - lSpeed;
                p = newError * Kp;
                d = oldError * Kd;
                totalError = p + d;
                speedAdjustR = RFULL_SPEED - totalError;
                speedAdjustL = LFULL_SPEED;
                oldError = newError;
            }
            else if (rSpeed < lSpeed) {
                newError = lSpeed - rSpeed;
                p = newError * Kp;
                d = oldError * Kd;
                totalError = p + d;
                speedAdjustL = LFULL_SPEED - totalError;
                speedAdjustR = RFULL_SPEED;
                oldError = newError;
            }
            else {
                speedAdjustR = RFULL_SPEED;
                speedAdjustL = LFULL_SPEED;
            }
            break;
        default:
            break;
    }
    //Transitions
    switch(ePID_State) {
        case INIT_3:
            ePID_State = CONTROL;
            break;
        case CONTROL:
            ePID_State = CONTROL;
            break;
        default:
            break;
    }


}

void Set_Init() {
    Serial.begin(9600);
    Set_State = INIT_4;
}

void Set_Tick() {
    
    //Actions
    switch(Set_State) {
        case INIT_4:
            break;
        case SET:
            Serial.print("Right Speed:" );
            Serial.println(speedAdjustR);
            Serial.print("Left Speed:" );
            Serial.println(speedAdjustL);
            forward(speedAdjustL, speedAdjustR);
            distance++;
            break;
        case STOP:
            breakMotors();
            distance++;
            break;
        default:
            break;
    }
    
    //Transitions
    switch(Set_State) {
        case INIT_4:
            Set_State = SET;
            break;
        case SET:
            
            if(distance < 100) {
                Set_State = SET;
            }
            else {
                distance = 0;
                Set_State = STOP;
            }
            //Set_State = SET;
            break;
        case STOP:
            if(distance < 40) {
                Set_State = STOP;
            }
            else {
                //distance = 0;
                Set_State = STOP;
            }
            break;
        default:
            break;
    }
}


#endif
