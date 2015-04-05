/*
 *
 *  File:         lcd_1.c
 *  Date:         19Feb2015
 *  Authors:      Alberto Heras, Timothy Luensman, Tommy May, Xinran Fang
 *
 */

#include "p24FJ64GA002.h"
#include "lcd.h"
#include "timer.h"

#define LCD_DATA   LATB
#define LCD_RS  LATBbits.LATB7
#define LCD_E   LATBbits.LATB6

#define TRIS_D7  TRISBbits.TRISB15
#define TRIS_D6  TRISBbits.TRISB14
#define TRIS_D5  TRISBbits.TRISB13
#define TRIS_D4  TRISBbits.TRISB12
#define TRIS_RS  TRISBbits.TRISB7
#define TRIS_E   TRISBbits.TRISB6

#define UPPER 0
#define LOWER 1

#define LCD_WRITE_DATA 1
#define LCD_WRITE_CONTROL 0
#define LCD_WRITE_DELAY 50
#define LCD_SET_DELAY 50
#define NO_DELAY 0

// These are just in case you cannot pass binary numbers as unsigned characters into the
// the write four bits function, the lower bits of the ascii values of these letters are the ones
// we need to make the initialization work.

#define BIT(x,n) (((x) >> (n)) & 1)
/*********************************************************************************************/

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower)
{
    if(lower)
    {
        LATBbits.LATB15 = BIT(word,3);
        LATBbits.LATB14 = BIT(word,2);
        LATBbits.LATB13 = BIT(word,1);
        LATBbits.LATB12 = BIT(word,0);
    }
    else
    {
        LATBbits.LATB15 = BIT(word,7);
        LATBbits.LATB14 = BIT(word,6);
        LATBbits.LATB13 = BIT(word,5);
        LATBbits.LATB12 = BIT(word,4);
    }

    LCD_RS = commandType;   // Write LCD_RS = 1;
    delayUs(1);
    LCD_E = 1;  delayUs(1); //minimum 230 ns
    LCD_E = 0;  delayUs(1);

    delayUs(delayAfter);
}

/*********************************************************************************************/

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter)
{
    writeFourBits(word, commandType, delayAfter, UPPER);
    writeFourBits(word, commandType, delayAfter, LOWER);
}

/*********************************************************************************************/

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c)
{
    writeLCD(c, LCD_WRITE_DATA, 50);
}

/*********************************************************************************************/

/*Initialize the LCD
 */
void initLCD(void) {

    // Setup D, RS, and E to be outputs (0).
    TRIS_D7 = 0;
    TRIS_D6 = 0;
    TRIS_D5 = 0;
    TRIS_D4 = 0;
    TRIS_E  = 0;
    TRIS_RS = 0;

    LCD_DATA = 0;

    // Initilization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.

    // Initial 15ms delay
    delayUs(15000);

    // Enable 4-bit interface
    writeFourBits(0b00110000, LCD_WRITE_CONTROL, 4200, UPPER);
    writeFourBits(0b00110000, LCD_WRITE_CONTROL, 120, UPPER);
    writeFourBits(0b00110000, LCD_WRITE_CONTROL, 120, UPPER);// Try 120 delay

    // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.
    writeFourBits(0b00000010, LCD_WRITE_CONTROL, 120, LOWER);// Try 120

    // Function Set
    writeLCD((0b00101000), LCD_WRITE_CONTROL, LCD_SET_DELAY);//

    // Turn Display (D) Off
    writeLCD(0b00001000, LCD_WRITE_CONTROL, LCD_SET_DELAY);

    // Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.
    writeLCD(0b00000001, LCD_WRITE_CONTROL, 1500);

    // Set Increment Display, No Shift (i.e. cursor move)
    writeLCD((0b00000110), LCD_WRITE_CONTROL, LCD_SET_DELAY);

    // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
    writeLCD((0b00001100), LCD_WRITE_CONTROL, LCD_SET_DELAY);

}

/*********************************************************************************************/
/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s)
{
    int i = 0;

    for( i = 0; s[i] != '\0'; i++)
    {
        writeLCD(s[i], LCD_WRITE_DATA, 46);
    }
}

/*********************************************************************************************/
/*
 * Clear the display.
 */
void clearLCD()
{
    writeLCD(0b00000001, LCD_WRITE_CONTROL, 1500);
}

/*********************************************************************************************/
/*
 * Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y)
{
       writeLCD( (0x80 + 0x40*x+y), LCD_WRITE_CONTROL, 50);
}

/*********************************************************************************************/
/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();
    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);

    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);

    for(i = 0; i < 1000; i++) delayUs(1000);

    printStringLCD("Hello!");

    for(i = 0; i < 1000; i++) delayUs(1000);
}

/*********************************************************************************************/
