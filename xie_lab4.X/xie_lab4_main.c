/*
 * File:   xie_lab4_main.c
 * Author: xieruide
 *
 * Created on June 30, 2020, 4:52 PM
 */


#include "xc.h"
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

void setup(){
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;
    TRISB=0xffff;
    TRISBbits.TRISB6=0;
    TRISBbits.TRISB8=1;
    LATB=0;
}

void initServo(void){
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPINR7bits.IC1R = 8;  // Use Pin RP8 = "8", for Input Capture 1 (Table 10-2)//////////
    RPOR3bits.RP6R = 18;  // Use Pin RP6 for Output Compare 1 = "18" (Table 10-3)
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS

    T3CON=0x0010;
    IFS0bits.T3IF=0;
    TMR3=0;
    PR3=39999;//   20ms/62.5ns/8-1
    T3CONbits.TON = 1;
    
    OC1CON = 0;    // turn off OC1 for now
    OC1R = 3999;   // servo start position. We won?t touch OC1R again
    OC1RS = 3999;  // We will only change this once PWM is turned on
    OC1CONbits.OCTSEL = 1; // Use Timer 3 for compare source
    OC1CONbits.OCM = 0b110; // Output compare PWM w/o faults  
}

void setServo(int Val){
    OC1RS=Val;
}

void initPushButton(void){
    T2CON=0b0000000000110000;//1:256
    PR2=62499;
    TMR2=0;
    _T2IF=0;    
    _CN22PUE = 1;
    _T2IE=1;
    T2CONbits.TON=1;
    
    T1CON=0b0000000000110000;//1:256
    PR1=62499;
    TMR1=0;
    _T1IF=0;  
    _T1IE=1;
    T1CONbits.TON=1;
    
    IC1CON = 0; // Turn off and reset internal state of IC1
    IC1CONbits.ICTMR = 1; // Use Timer 2 for capture source
    IC1CONbits.ICM = 0b010; // Turn on and capture every falling edge
    IC1CON = 1;
    _IC1IF = 0;
    _IC1IE = 1; 
    
}
volatile int  rollover1 = 0;
void __attribute__((interrupt, auto_psv)) _T1Interrupt(){
    rollover1++;
    IFS0bits.T1IF=0;
}
volatile int  rollover = 0;
void __attribute__((interrupt, auto_psv)) _T2Interrupt(){
    rollover++;
    IFS0bits.T2IF=0;
}

 volatile int signal=0,flag=0;
 volatile unsigned long start,diff,end;
//unsigned long long int arr[2]={0,0};
//volatile unsigned long long int curPeriod=0;
    
//   _IC1IF = 0;   
//   start=IC1BUF;
//   //while(PORTBbits.RB8==0);
//   end=IC1BUF;
//   val=end+62500*rollover-start;
//   if(val>125){
//       TMR2=0;
//       rollover=0;
//       signal=1;
//    }

int r;
void __attribute__((__interrupt__,__auto_psv__)) _IC1Interrupt(void) { 
    _IC1IF = 0; 
    end=IC1BUF;
    diff=end+62500*rollover-start-r*62500;
    if(diff>1250){
        if(diff>15625 && diff<53125){
            flag=1;
        }
        start=end;
        r=rollover;
    }
}

int main(void) {
//    unsigned long long int interval;
    setup();
    initServo();
    initPushButton();
//    int prevState,curState=1;
    while(1){
        if(flag==1){
            setServo(35999);
            flag=0;
            TMR2=0;
            rollover=0;
            }
        if(rollover==2){
            setServo(3999);
            }
        } 
//    unsigned long long int t1,t2;
//    double diff;
//    while(1){
//        curState=PORTBbits.RB8;            
//        if(curState==0 && prevState == 1){
//            xie_wait_1ms();
//            xie_wait_1ms();          
//            curState=PORTBbits.RB8;
//            if(curState==0 && prevState==1){                
//                t2=TMR2+rollover*62500;
//                diff=(t2-t1)*256*0.0000000625;
//                if(diff<0.25){
//                    setServo(35999);
//                    int i;
//                    for(i=0;i<2000;i++){
//                        xie_wait_1ms();
//                    }
//                    setServo(3999);
//                }else{
//                    setServo(3999);
//                }
//                t1=t2;
//            } 
//        }  
//        prevState=curState;
//        xie_wait_1ms();
//        xie_wait_1ms(); 
//    }  
   
    
//    int t=0;
//    while(1){
//        if(signal==1){
//            if(t%3!=0){
//                _IC1IE = 0;
//                TMR2=0;
//                while(PORTBbits.RB8==1);
//                interval=TMR2+62500*rollover;
//                curPeriod=interval+val;
//                _IC1IE = 1;
//                if(curPeriod<15625){
//                    if(arr[0]==0){
//                        arr[0]=curPeriod;
//                    }
//                    if(arr[0]!=0 && arr[1]==0){
//                        arr[0]=0;
//                        setServo(35999);
//                    int i;
//                    for(i=0;i<2000;i++){
//                        xie_wait_1ms();
//                    }
//                        setServo(3999);
//                    }  
//                }
//            } 
//            signal=0; 
//            t++;
//            if((TMR2+62500*rollover)>12500){
//                t=0;
//                arr[0]=0;
//                arr[1]=0;
//            }
//        }
//    }
    return 0;
}
