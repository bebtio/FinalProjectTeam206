/*
 *
 *  File:         timer.c
 *  Date:         19Feb2015
 *  Authors:      Alberto Heras, Timothy Luensman, Tommy May, Xinran Fang
 *
 */

#include "p24FJ64GA002.h"
#include "timer.h"
#include <stdio.h>


#define FCY 14745600.0
#define waitTimeMicro .000001 // 1 microsecond
#define waitTimeMilli .001 // 1 millisecond


/*********************************************************************************************/
// Delays for a certain number of micro seconds

void delayUs(unsigned int delay){

    T1CONbits.TCKPS = 0b00;
    TMR1 = 0;
    PR1 = ((FCY*waitTimeMicro*delay)/1.0) - 1.0;
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 1;
    while(IFS0bits.T1IF == 0); // While the flag is down, stay in while loop
    IFS0bits.T1IF = 0; // Put the flag down afterwards.
    T1CONbits.TON = 0; // Turn the timer off so it does not keep counting.

}

/*********************************************************************************************/

/*********************************************************************************************/
// Delays for a certain number of milli seconds

void delayMs(unsigned int delay){

    T1CONbits.TCKPS = 0b11;
    TMR1 = 0;
    PR1 = ((FCY*waitTimeMilli*delay)/256) - 1.0;
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 1;
    while(IFS0bits.T1IF == 0); // While the flag is down, stay in while loop
    IFS0bits.T1IF = 0; // Put the flag down afterwards.
    T1CONbits.TON = 0; // Turn the timer off so it does not keep counting.

}

