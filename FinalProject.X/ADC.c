/*
 * File:   ADC.c
 * Author: albertoheras, thomasmay,timothyleunsman, xinranfang
 *
 *
 */
#include "p24FJ64GA002.h"
#include "ADC.h"
#include "LCD.h"
#include <stdio.h>
#include <stdlib.h>
#include "shared.h"
#include "timer.h"

/******************************************************************************/

// Initializes the ADC to read an analog voltage from the potentiometer
void initADC()
{

    AD1PCFG = 0xFFFE;      // Set pin 25 to analog for reading
    AD1CON1bits.FORM = 0;       // Output formatted as an integer
    AD1CON1bits.SSRC = 0b0111;  // Auto internal clock usage
    AD1CON1bits.ASAM = 0;       // Auto start sampling
    AD1CON2bits.VCFG = 0;       // Uses system voltage for reference voltages
    AD1CON2bits.CSCNA = 0;      // Uses CH0SA bits as MUXA input, inputs only work on MUXA
    AD1CON2bits.SMPI = 0b1111;  // Interrupt at 16th sample convert sequence
    AD1CON2bits.ALTS = 0;       // Always uses MUXA input multiplexor settings
    AD1CON3bits.ADRC = 0;       // Uses system clock for conversions
    AD1CON3bits.SAMC = 1;       // 1 = use TAD
    AD1CON3bits.ADCS = 10;      // Clock period select bits = 10 so *FCY
    AD1CHS = 0;                 // Connect pin as positive input: AN0
    AD1CSSL = 0;                // Channel scanning is disabled anyway.
    AD1CON1bits.ADON = 1;       // Turn on A/D

//    IEC0bits.AD1IE = 1;         //Enable the interrupt
    IFS0bits.AD1IF = 0;         //Put the flag down
}

/******************************************************************************/

// Takes value from the ADC buffer and returns that value
int readAnalogVoltage()
{
    float analogVoltage = 0;
    unsigned int *ADCPtr;
    ADCPtr = (unsigned int*) &ADC1BUF0;
    IFS0bits.AD1IF = 0; // Puts A/D flag down

   
    AD1CON1bits.ASAM = ON;       // Starts Auto Sampling
    while (!IFS0bits.AD1IF){};  // Waits for sampling to finish
    AD1CON1bits.ASAM = OFF;       // Stops sampling

    analogVoltage = analogVoltage + *ADCPtr++;

    return(analogVoltage);
}

/******************************************************************************/

// Reads the voltage from the ADC and displays the value on the LCD
void printAnalogVoltageLCD()
{
    int i = 0;
    char voltageStr[7];

    // Reads Voltage: Takes Average over 100 iterations
    double voltage = 0;
    for(i = 0; i< 100; i++)
    {
        // Divides read value by bit depth and multiplies by 5 to get Voltage
        voltage = (voltage + 5*readAnalogVoltage()/1023.0);
    }
    voltage = voltage/100.0;

    // If the current voltage is different enough from the previous voltage
    // Update the LCD voltage value
    if(voltage > previousVoltage + .0025 || voltage < previousVoltage -.0025)
    {
            previousVoltage = voltage;
            
            moveCursorLCD(0,0);// Creates to store string
            sprintf(voltageStr, "%.2f V", voltage);             
            printStringLCD(voltageStr);   
    }
}

/******************************************************************************/
