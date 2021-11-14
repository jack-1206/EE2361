/*
 * File:   xie_lab5_main.c
 * Author: xieruide
 *
 * Created on July 15, 2020, 11:47 AM
 */
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

#include "xc.h"
#include "string.h"
#include "delay.h"
int a=0b0000,b=0b10;
void setup(){
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;
    TRISAbits.TRISA0=0;
    I2C2BRG=0x9d;
    I2C2CONbits.I2CEN=0;
    I2C2CONbits.I2CEN=1;
    IFS3bits.MI2C2IF=0;
}

void lcd_cmd(char Package){
    I2C2CONbits.SEN=1;
    while(I2C2CONbits.SEN==1);
    IFS3bits.MI2C2IF=0;
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(IFS3bits.MI2C2IF == 0 );// *Refer to NOTE below*
    IFS3bits.MI2C2IF=0;
    I2C2TRN = 0b00000000; // 8-bits consisting of control byte
    while(IFS3bits.MI2C2IF == 0 );
    IFS3bits.MI2C2IF=0;
    I2C2TRN = Package; // 8-bits consisting of the data byte
    while(IFS3bits.MI2C2IF == 0 );
    IFS3bits.MI2C2IF=0;
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN==1); // PEN will clear when Stop bit is complete
}

void lcd_init(void){
    int i;
    for(i=0;i<50;i++){
        xie_wait_1ms();
    }
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00111001); // function set, extended instruction mode
    lcd_cmd(0b00010100); // interval osc
    lcd_cmd(0b01110000|a); // contrast C3-C0
    lcd_cmd(0b01010100|b); // Ion, Bon, C5-C4
    lcd_cmd(0b01101100); // follower control
    for(i=0;i<200;i++){
        xie_wait_1ms();
    }
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00001100); // Display On
    lcd_cmd(0b00000001); // Clear Display
    xie_wait_1ms();
    xie_wait_1ms();
}

void lcd_setCursor(char x, char y){
    lcd_cmd(0b10000000|(0x40*y+x));
}

 void lcd_printChar(char Package) {
    I2C2CONbits.SEN= 1;	//Initiate Start condition
    while(I2C2CONbits.SEN==1);  // SEN will clear when Start Bit is complete
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(IFS3bits.MI2C2IF==0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01000000; // 8-bits consisting of control byte /w RS=1
    while(IFS3bits.MI2C2IF==0);
    IFS3bits.MI2C2IF=0;
    I2C2TRN = Package; // 8-bits consisting of the data byte
    while(IFS3bits.MI2C2IF==0);
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN==1); // PEN will clear when Stop bit is complete
}
 
void lcd_printStr(const char s[]){
    int size=strlen(s);
    I2C2CONbits.SEN= 1;	//Initiate Start condition
    while(I2C2CONbits.SEN==1);  // SEN will clear when Start Bit is complete
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(IFS3bits.MI2C2IF==0);
    IFS3bits.MI2C2IF = 0;
    int i;
    for(i=0;i<size-1;i++){
        I2C2TRN = 0b11000000; // 8-bits consisting of control byte /w RS=1
        while (IFS3bits.MI2C2IF==0);
        IFS3bits.MI2C2IF = 0;
        I2C2TRN = s[i]; // 8-bits consisting of the data byte
        while (IFS3bits.MI2C2IF==0);
        IFS3bits.MI2C2IF = 0;
    }
    I2C2TRN = 0b01000000; // 8-bits consisting of control byte /w RS=1, Co=0
    while (IFS3bits.MI2C2IF==0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = s[size-1]; // 8-bits consisting of the data byte
    while (IFS3bits.MI2C2IF==0);
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN==1); // PEN will clear when Stop bit is complete
}

int main(void) {
    setup();
    lcd_init();
    lcd_setCursor(0,0);
    lcd_printStr("Hello");
    lcd_setCursor(2,1);
    lcd_printStr("World!");
    while (1) {
       int i;
       for(i=0;i<300;i++){
            xie_wait_1ms();
        } 
       lcd_cmd(0b0000011000);//shifting: lcd data sheet page 22
    }
    return 0;
}

