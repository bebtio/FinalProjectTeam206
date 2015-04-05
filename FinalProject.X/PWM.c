/*
 * File:   PWM.c
 * Author: albertoheras, thomasmay,timothyleunsman, xinranfang
 *
 *
 */
#include "p24FJ64GA002.h"
#include "PWM.h"

#define FCY 14745600.0                       // System Frequency
#define TTOT .001                            // Total time signal is high
#define PRVAL (((TTOT*FCY)/(1)) - 1.0)       
#define SIMPLEPWMMODE 0b0110

#define OCM_1 18
#define OCM_2 19
#define OCM_3 20
#define OCM_4 21

#define TRIS_H15 TRISBbits.TRISB10
#define TRIS_H10 TRISBbits.TRISB11
#define TRIS_H2 TRISAbits.TRISA3
#define TRIS_H7 TRISAbits.TRISA4

#define LAT_H15 LATBbits.LATB10
#define LAT_H10 LATBbits.LATB11
#define LAT_H2 LATAbits.LATA3
#define LAT_H7 LATAbits.LATA4
                     

/************************************************************************************/

// Initializes the PWM module
void initPWM(){


    TRIS_H15 = 0;
    TRIS_H10 = 0;
    TRIS_H2 = 0;
    TRIS_H7 = 0;

    LAT_H15 = 1;
    LAT_H10 = 1;
    LAT_H2 = 1;
    LAT_H7 = 1;

    TMR2 = 0;               // Resets Timer 2
    T2CONbits.TCKPS = 0b00; // prescalar of 1 for more acurrate output
    PR2 = PRVAL;            // Sets PRVAL
 
    // Initialize duty cycle to zero
    OC1R = 0;
    OC2R = 0;
    OC3R = 0;
    OC4R = 0;

    OC1RS = 0;
    OC2RS = 0;
    OC3RS = 0;
    OC4RS = 0;
    
    // Selects Timer 2
    OC1CONbits.OCTSEL = 0;
    OC2CONbits.OCTSEL = 0;
    OC3CONbits.OCTSEL = 0;
    OC4CONbits.OCTSEL = 0;

    // Sets Simple PWM Mode
    OC1CONbits.OCM = SIMPLEPWMMODE;
    OC2CONbits.OCM = SIMPLEPWMMODE;
    OC3CONbits.OCM = SIMPLEPWMMODE;
    OC4CONbits.OCM = SIMPLEPWMMODE;


    // Right Motor
    RPOR1bits.RP2R = OCM_1;   // RP2R map OC1 to pin H-BRIDGE/PIC246 = 15/6
    RPOR1bits.RP3R = OCM_3;   // map OC3 to pin H-BRIDGE/PIC246 = 10/7

    // Left Motor
    RPOR2bits.RP5R = OCM_2;   // map OC2 to pin H-BRIDGE/PIC246 = 2/14
    RPOR4bits.RP8R = OCM_4;   // map OC4 to pin H-BRIDGE/PIC246 = 7/17

    // Turn on Timer2
    T2CONbits.TON = 1;      
    
}

/************************************************************************************/

// Sets or changes the current duty cycle
void setDutyCycleOCM1(float dutyCycle)
{
    OC1RS = PRVAL*dutyCycle;
}

/************************************************************************************/

void setDutyCycleOCM2(float dutyCycle)
{
    OC2RS = PRVAL*dutyCycle;
}

/************************************************************************************/

void setDutyCycleOCM3(float dutyCycle)
{
    OC3RS = PRVAL*dutyCycle;
}

/************************************************************************************/


void setDutyCycleOCM4(float dutyCycle)
{
    OC4RS = PRVAL*dutyCycle;
}

/************************************************************************************/
