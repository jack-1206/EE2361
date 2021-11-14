/*
 * File:   xie_lab1_main_v001.c
 * Author: xieruide
 *
 * Created on June 8, 2020, 11:30 AM
 */


#include "xc.h"
// CONFIG0
#pragma config POSCMOD = NONE      // Primary Oscillator Select (Primary oscillator disabled)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as port I/O (RC15))
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#pragma config SOSCSEL = SOSC      // Sec Oscillator Select (Default Secondary Oscillator (SOSC))
#pragma config WUTSEL = LEG        // Wake-up timer Select (Legacy Wake-up Timer)
#pragma config IESO = ON           // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)?rotection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)



void setup(void){
    AD1PCFG = 0x9fff;            //sets all pins to digital I/O
    TRISA = 0b0000000000011111;  //set port A to inputs, 
    TRISB = 0b0000000000000011;  //and port B to outputs
    LATA = 0xffff;               //Set all of port A to HIGH
    LATB = 0xffff;               //and all of port B to HIGH
    
}

/*  main(void) {
    setup();
    //LATB = 0x0FFF;
    while(1) {
        //LATB &= 0xAFFF; 
        LATB = LATB | 0x3000;
    }
    return 0;
}*/
void delay(void) {
    int curCount = 0;
    
    while(curCount < 4000)
    {
        curCount++;
    }
}

/*int main(void) {
    setup(); 
    LATB = 0x7FFF; //This will turn on the most significant LED
                  
    while(1) {
        // Execute repeatedly forever and ever and ever and ever ...   
        delay(); //This pauses execution so the shifts are visible 
        LATB = LATB >> 1; //This shifts the LATB register
        LATB |= 0x8000;         
    }
    return 0;
}*/

int main(void) {
    setup();
    LATB = LATB >> 1;
    delay();
    while(1) {
        // Execute repeatedly forever and ever and ever and ever ...           
        LATB = (LATB >> 1) | 0x8000;
        delay();
        LATB = (LATB >> 1) | 0x8000;
        delay();
        LATB = (LATB >> 1) | 0x8000;
        delay();
        LATB = (LATB << 1) | 0x1001;
        delay();
        LATB = (LATB << 1) | 0x1003;
        delay();
        LATB = (LATB << 1) | 0x1007;
        delay();
    }
    return 0;
}