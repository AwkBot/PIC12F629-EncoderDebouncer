/*
 * File:   main.c
 * Author: Carlos
 *
 * Created on June 20, 2021, 12:43 PM
 * 
 * Reference:
 * Pin 1 - RA2 - Encoder Clock
 * Pin 2 - RA3 - Encoder Data
 * Pin 18 - RA1 - Clockwise Pulse
 * Pin 14 - RA0 - Counter-Clockwise Pulse
 */

// Fuse Bits Configuration
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#define _XTAL_FREQ 4000000      // MCU Internal Oscilator Frequency

// Includes
#include "main.h"
#include "encoder.h"

void main(void) {
  int8_t tmpEncValue;
  int8_t counter = 0x00;
  
  // Initialization
  CMCON  = 0x07; // Disable Comparators
  INTCON = 0x00; // Disable all interruption
  
  // Setup GPIO
  TRISIO0 = 0;  // Input Pin
  TRISIO1 = 0;  // Input Pin
  WPU4    = 1;  // Pull-Up
  WPU5    = 1;  // Pull-Up
  TRISIO4 = 1;  // Output Pin
  TRISIO5 = 1;  // Output Pin
  
  // Set two outputs as High
  outPlus  = 1;
  outMinus = 1;
  
  // Infinity looping
  while(1){
    // Read Encoder
    tmpEncValue = read_encoder();
    counter -= tmpEncValue;
    
    // Identify the 4th change in encoder in sync with the click
    if(((counter % 4) == 0) && (tmpEncValue != 0)) {
      // Generate clockwise pulse
      if(counter < 0) {
        outPlus = 0;
        __delay_ms(INT_PULSE_DURATION);
        outPlus = 1;
      }
      // Generate counter-clockwise pulse
      else {
        outMinus = 0;
        __delay_ms(INT_PULSE_DURATION);
        outMinus = 1;
      }

      // Reset counter
      counter = 0;
    }
    __delay_ms(2);
  }
}
