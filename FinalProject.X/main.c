/*
 * File:   main.c
 * Author: albertoheras, thomasmay,timothyleunsman, xinranfang
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "p24FJ64GA002.h"
#include "stateFunctions.h"
#include "shared.h"
#include "ADC.h"
#include "PWM.h"
#include "LCD.h"
#include "timer.h"
#include "motors.h"

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

/************************************************************************/

int main(int argc, char** argv)
{ 
    while(1)
    {
        //FSM implementation
        switch(currentState)
        {
            case initState: init_state();
                break;
            case idleState: idle_state();
                break;
            case forwardState: forward_state();
                break;
            case backwardState: backward_state();
                break;
            case debouncePressState: debounce_press_state();
                break;
        }
    }

    return (EXIT_SUCCESS);
}

/************************************************************************/

void _ISR _CNInterrupt(void)
{
    IFS1bits.CNIF = 0;
    // If the State button is pressed, change states
    if(SWITCH == PRESSED)
    {
        currentState = debouncePressState;
    }
    
}

/************************************************************************/
