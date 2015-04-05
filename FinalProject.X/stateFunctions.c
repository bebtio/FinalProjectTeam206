/*
 * File:   stateFunctions.c
 * Author: albertoheras, thomasmay,timothyleunsman, xinranfang
 *
 *
 */
#include "stateFunctions.h"
#include "shared.h"
#include "motors.h"
#include "PWM.h"
#include "ADC.h"
#include "LCD.h"
#include "timer.h"
#include "switches.h"
#include "p24FJ64GA002.h"

/************************************************************************/

// Initializes All the modules, motors, switches, and sets the set to idleState.
void init_state()
{
    initPWM();
    initLCD();
    initMotors();
    initADC();
    initStateButton();
    currentState = idleState;
    previousVoltage = readAnalogVoltage();
    printAnalogVoltageLCD();
    lastState = 0;
}

/************************************************************************/

// Moves the robot forward, angle is controlled by the potentiometer
// Also prints "Forward" to LCD
void forward_state()
{
    moveCursorLCD(1,0);
    printStringLCD("Forward");
    moveForward();
    printAnalogVoltageLCD();
}

/************************************************************************/

// Moves Robot backwards, angle is controlled by the potentiometer
// Prints "Back" to LCD
void backward_state()
{
    moveCursorLCD(1,0);
    printStringLCD("Back");
    moveBackward();
    printAnalogVoltageLCD();
}

/************************************************************************/

// Stops the motion of the robot
// Prints "Idle" to LCD
void idle_state()
{
    moveCursorLCD(1,0);
    printStringLCD("Idle");
    STOP();
    printAnalogVoltageLCD();
}

/************************************************************************/

// Debounces the state switch and decides the next state
void debounce_press_state()
{
    delayMs(100);
    while(SWITCH == PRESSED);
    delayMs(100);

    if(SWITCH == RELEASED)
    {
        // This cylces throught values 1 through 4 and repeats.
        lastState = lastState%4 +1;

        if(lastState == 1)
        {
            currentState = forwardState;
        }
        else if(lastState == 3)
        {
            currentState = backwardState;
        }
         else 
        {
            currentState = idleState;
        }

        moveCursorLCD(1,0);
        printStringLCD("        ");
    }

    
}

/************************************************************************/