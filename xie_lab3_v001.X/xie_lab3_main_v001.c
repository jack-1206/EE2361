/*
 * File:   xie_lab3_main_v001.c
 * Author: xieruide
 *
 * Created on June 20, 2020, 11:16 PM
 */


#include "xc.h"
#include "seg.h"
#include "keypad.h"
#include "delay.h"
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))


void setup(void){
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;
    TRISA = 0;
    TRISB = 0;
    LATB = 0x0000;
    LATA = 0x0000;
}

int main(void) {   
    init7seg();
    initKeyPad();
    char pressedKey,Key='n';
    char old, new='n';
    while(1)
    {   
        pressedKey = Key;
        Key =readKeyPadRAW();
        if ((Key !='n') && (new!=pressedKey)){
            old=new;
            new=Key;       
        }
        showChar7seg(old,1);
        xie_wait_1ms();
        xie_wait_1ms();
        xie_wait_1ms();
        xie_wait_1ms();
        xie_wait_1ms();
        showChar7seg(new,0);
        xie_wait_1ms();
        xie_wait_1ms();
        xie_wait_1ms();
        xie_wait_1ms();
        xie_wait_1ms();

//        xieTest7seg();
    }
    return 0;
}
