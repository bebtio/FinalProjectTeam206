/*
 * File:   switches.h
 * Author: albertoheras, thomasmay,timothyleunsman, xinranfang
 *
 *
 */
#include "switches.h"
#include "p24FJ64GA002.h"

#define TRIS_Pin3 TRISAbits.TRISA1
/*********************************************************************************************/



/*********************************************************************************************/
//
void initStateButton(){
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
    TRIS_Pin3 = 1;
    AD1PCFGbits.PCFG1= 1;//AD1PCFGbits.PCFG4 = 1; // Analog input enable
    CNPU1bits.CN3PUE = 1;//CNPU1bits.CN6PUE = 1; // Pull Up resistor
    IEC1bits.CNIE = 1; // interrupt enable for board
    CNEN1bits.CN3IE = 1;//CNEN1bits.CN6IE = 1; // interrupt enable for the pin
    IFS1bits.CNIF = 0; // interrupt flag down
    IPC4bits.CNIP = 7;//IPC4bits.CNIP=7;
}

/*********************************************************************************************/