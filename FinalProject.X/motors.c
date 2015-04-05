/*
 * File:   motors.c
 * Author: albertoheras, thomasmay,timothyleunsman, xinranfang
 *
 *
 */
#include "motors.h"
#include "PWM.h"
#include "p24FJ64GA002.h"
#include "ADC.h"

// if Duty cycle is higher than PR, then voltage stays high
#define HIGH_RIGHT 2-(readAnalogVoltage()/512.0) 
#define HIGH_LEFT readAnalogVoltage()/(512.0)

// if duty cycle is 0, then voltage stays low
#define LOW 0
#define ON 1
#define enable LATBbits.LATB0
#define enable_pin TRISBbits.TRISB0



/**************************************************************************************/

// Initialize the enable pin for the motors and disable the motors for initialization
void initMotors()
{
    enable_pin = ON;
    enable = LOW;
}

/**************************************************************************************/

// This moves the robot forward by calling the functions that move each
// wheel forward independently
void moveForward()
{
    LWForward();
    RWForward();
}

/**************************************************************************************/

// This moves the robot backward by calling the functions that move each
// wheel backward independently
void moveBackward()
{
    LWBackward();
    RWBackward();

}

/**************************************************************************************/

// Stops the robots motions by setting all Duty cylces equal to eachother
void STOP()
{
    setDutyCycleOCM1(LOW);
    setDutyCycleOCM3(LOW);

    setDutyCycleOCM2(LOW);
    setDutyCycleOCM4(LOW);
    enable = 0;
}

/**************************************************************************************/

// Moves the Left wheel forward at rate determined by HIGH_LEFT function/equation
void LWForward()
{
    enable = 1;
    setDutyCycleOCM2(HIGH_LEFT);
    setDutyCycleOCM4(LOW);
}

/**************************************************************************************/

// Moves the Right wheel forward at rate determined by HIGH_RIGHT function/equation
void RWForward()
{
    enable = 1;
    setDutyCycleOCM3(HIGH_RIGHT);
    setDutyCycleOCM1(LOW);
}

/**************************************************************************************/

// Moves the Right wheel backward at rate determined by HIGH_RIGHT function/equation
void RWBackward()
{
    enable = 1;
    setDutyCycleOCM3(LOW);
    setDutyCycleOCM1(HIGH_RIGHT);
}

/**************************************************************************************/

// Moves the Left wheel bacwkard at rate determined by HIGH_LEFT function/equation
void LWBackward()
{
    enable = 1;
    setDutyCycleOCM2(LOW);
    setDutyCycleOCM4(HIGH_LEFT);
}

/**************************************************************************************/
