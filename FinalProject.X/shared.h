/*
 * File:   shared.h
 * Author: albertoheras, thomasmay,timothyleunsman, xinranfang
 *
 *
 */

#ifndef SHARED_H
#define	SHARED_H

/*********************************************************************************************/


// Define ON and OFF
#define ON   1
#define OFF  0

// Define btton presses
#define PRESSED 0
#define RELEASED 1
#define SWITCH PORTAbits.RA1

/*********************************************************************************************/

// State variables
typedef enum
{
    initState,
    idleState,
    forwardState,
    backwardState,
    debouncePressState

} stateType;

extern volatile stateType currentState;
extern volatile int previousVoltage;
extern volatile int lastState;

#endif	/* SHARED_H */

/*********************************************************************************************/



