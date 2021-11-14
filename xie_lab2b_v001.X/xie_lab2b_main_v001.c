/*
 * File:   xie_lab2b_main_v001.c
 * Author: xieruide
 *
 * Created on June 16, 2020, 4:32 PM
 */


#include "xc.h"
#include "xie_lab2b_asmLib_v001.h"
#include "stdint.h"
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

#define PERIOD 5
void setup(void){
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;
    TRISA = 0b1111111111111110;
    LATA = 0x0000;
}

void writeColor(int r, int g, int b){
    xie_wait_100us();
    int i;
    for(i=7; i>=0; i--){
        if((r&(1<<i))==0){
            write_0();
        }else{
            write_1();
        }
    }
    int j;
    for(j=7; j>=0; j--){
        if((g&(1<<j))==0){
            write_0();
        }else{
            write_1();
        }
    }
    int k;
    for(k=7; k>=0; k--){
        if((b&(1<<k))==0){
            write_0();
        }else{
            write_1();
        }
    }
}

void delay(int delay_in_ms){
    int i;
    for(i=0;i<delay_in_ms;i++){
        xie_wait_1ms();
    }
}

unsigned long int packColor(unsigned char Red, unsigned char Grn, unsigned char Blu){
    unsigned long int RGBval = 0;
    RGBval = ((long) Red << 16) | ((long) Grn << 8) | ((long) Blu);
    return RGBval;
}

unsigned char getR(uint32_t RGBval){
    unsigned char Red = 0;
    Red = (unsigned char) (RGBval >> 16);
    return Red;
}

unsigned char getG(uint32_t RGBval){
    unsigned char Green = 0;
    Green = (unsigned char) (RGBval >> 8 );
    return Green;
}
unsigned char getB(uint32_t RGBval){
    unsigned char Blue = 0;
    Blue  = (unsigned char) (RGBval >> 0 );
    return Blue;
}

void writePacCol(uint32_t PackedColor){
    unsigned char red=getR(PackedColor);
    unsigned char green=getG(PackedColor);
    unsigned char blue=getB(PackedColor);
    writeColor(red,green,blue);
}

uint32_t Wheel(unsigned char WheelPos){
    WheelPos=255 - WheelPos;
    if(WheelPos < 85) {
        return packColor(255 - WheelPos * 3, 0, WheelPos * 3);
  }
    if(WheelPos < 170) {
        WheelPos -= 85;
        return packColor(0, WheelPos * 3, 255 - WheelPos * 3);
  }
    WheelPos -= 170;
    return packColor(WheelPos * 3, 255 - WheelPos * 3, 0);
}

int main(void) {
    setup();
    xie_wait_100us();
    while(1){
//        writeColor(255,0,0);
//     write_1();
//     write_1();
//     write_1();
//     write_1();   
//     write_1();
//     write_1();
//     write_1();
//     write_1();
//
//     write_0();
//     write_0();
//     write_0();
//     write_0();
//     write_0();
//     write_0();
//     write_0();
//     write_0();  
//     write_0();
//     write_0();
//     write_0();
//     write_0();   
//     write_0();
//     write_0();
//     write_0();
//     write_0();
//     delay(10);
        int FrameNumber;
//        for(FrameNumber=255; FrameNumber>=0; FrameNumber--){
//            writeColor(FrameNumber, 0, 255-FrameNumber);
//            delay(10);
//        }
        for(FrameNumber = 0;  FrameNumber<= 255; FrameNumber++){
//            writeColor(FrameNumber, 0, 255-FrameNumber);            
            uint32_t wheelVar=Wheel(FrameNumber);//changing every color
            writePacCol(wheelVar);
            delay(10);
        }        
    }
    return 0;
}
