/*
 * File:   main.c
 * Author: Nerijus
 * MPLAB X IDE v2.00
 * Compiler C18 v3.47
 * Programmer PICkit 3
 * Created on 2014.03.17
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <p18f4550.h>
#include <delays.h>
#include <xlcd.h>
 
#pragma config FOSC = HSPLL_HS    // Using 20 MHz crystal with PLL
#pragma config PLLDIV = 5         // Divide by 5 to provide the 96 MHz PLL with 4 MHz input
#pragma config CPUDIV = OSC1_PLL2 // Divide 96 MHz PLL output by 2 to get 48 MHz system clock
#pragma config FCMEN = OFF        // Disable Fail-Safe Clock Monitor
#pragma config IESO = OFF         // Disable Oscillator Switchover mode
#pragma config PWRT = OFF         // Disable Power-up timer
#pragma config BOR = OFF          // Disable Brown-out reset
#pragma config WDT = OFF          // Disable Watchdog timer
#pragma config MCLRE = ON         // Enable MCLR Enable
#pragma config LVP = OFF          // Disable low voltage ICSP
#pragma config ICPRT = OFF        // Disable dedicated programming port (only on 44-pin devices)
#pragma config CP0 = OFF          // Disable code protection
  
//**** Delay functions for xlcd.h **************************************************************************
  
void DelayFor18TCY(void) {                             // dalay for 20 TCY
    Delay10TCYx(2);
}
  
void DelayPORXLCD(){                                  // delay for 15 ms
    Delay10KTCYx(20);
}
 
void DelayXLCD(){                                     // delay for 5 ms
    Delay10KTCYx(7);
}
 
//*********************************************************************************************************
 
//***** Some text for display *****************************************************************************
 
char LCD_text1[] = "  LCD DISPLAY & ";
char LCD_text2[] = "   PIC18F4550   ";
 
//*********************************************************************************************************
 
void main(void) {
    ADCON1 = 0b11111111;                            // Configure all pins digital
                                                    // For me it not want work without it
     
//********  Configure LCD for four line communication and 5X7 line display *********************************
 
    OpenXLCD(FOUR_BIT  & LINES_5X7);
    while( BusyXLCD() );                           //wait untill LCD controller is busy
 
    WriteCmdXLCD(CURSOR_OFF);
    while( BusyXLCD() );
    WriteCmdXLCD(BLINK_OFF);
    while( BusyXLCD() );
 
//*************************************************************************************************************
 
    while(1){
 
//*********** Set the starting address in the LCD RAM for display. This determines the location of display ********
 
        SetDDRamAddr(0x80);
        while( BusyXLCD() );                        //wait untill LCD controller is busy
        putsXLCD(LCD_text1);                        //Display string of text
        while( BusyXLCD() );                        //wait untill LCD controller is busy
    
//********** Set the address in second line for display ****************************************************
 
        SetDDRamAddr(0xC0);
        while( BusyXLCD() );                        //wait untill LCD controller is busy
        putsXLCD(LCD_text2);                        //Display string of text
        while( BusyXLCD() );                        //wait untill LCD controller is busy
 
        WriteCmdXLCD(SHIFT_DISP_LEFT);
        while( BusyXLCD() );
    }
}
