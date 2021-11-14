/*
 * File:   seg.c
 * Author: xieruide
 *
 * Created on June 24, 2020, 1:06 PM
 */


#include "xc.h"
#include "seg.h"
#include "delay.h"
void init7seg(void){
    setup();
    TRISB |= 0b0000000000000011;
}


void showChar7seg(char myChar, int myDigit){
    LATB = 0xf000;
    if(myDigit==0){
        if(myChar=='0'){
            LATB|=0x080f;
        }
        else if (myChar=='1'){
            LATB|=0x0a7f;
        }
        else if (myChar=='2'){
            LATB|=0x0897;
        }
        else if(myChar=='3'){
            LATB|=0x0837;
        }
        else if(myChar=='4'){
            LATB|=0x0a67;
        }
        else if(myChar=='5'){
            LATB|=0x0927;
        }
        else if(myChar=='6'){
            LATB|=0x0907;
        }
        else if(myChar=='7'){
            LATB|=0x087f;
        }
        else if(myChar=='8'){
            LATB|=0x0807;
        }
        else if(myChar=='9'){
            LATB|=0x0827;
        }
        else if(myChar=='A'){
            LATB|=0x0847;
        }
        else if(myChar=='b'){
            LATB|=0x0b07;
        }
        else if(myChar=='C'){
            LATB|=0x098f;
        }
        else if(myChar=='d'){
            LATB|=0x0a17;
        }
        else if(myChar=='E'){
            LATB|=0x0987;
        }
        else if(myChar=='F'){
            LATB|=0x09c7;
        }
    }
    if(myDigit==1){
        if(myChar=='0'){
            LATB|=0x040f;
        }
        else if (myChar=='1'){
            LATB|=0x067F;
        }
        else if (myChar=='2'){
            LATB|=0x0497;
        }
        else if(myChar=='3'){
            LATB|=0x0437;
        }
        else if(myChar=='4'){
            LATB|=0x0667;
        }
        else if(myChar=='5'){
            LATB|=0x0527;
        }
        else if(myChar=='6'){
            LATB|=0x0507;
        }
        else if(myChar=='7'){
            LATB|=0x047f;
        }
        else if(myChar=='8'){
            LATB|=0x0407;
        }
        else if(myChar=='9'){
            LATB|=0x0427;
        }
        else if(myChar=='A'){
            LATB|=0x0447;
        }
        else if(myChar=='b'){
            LATB|=0x0707;
        }
        else if(myChar=='C'){
            LATB|=0x058f;
        }
        else if(myChar=='d'){
            LATB|=0x0617;
        }
        else if(myChar=='E'){
            LATB|=0x0587;
        }
        else if(myChar=='F'){
            LATB|=0x05c7;
        }      
    }
}

void xieTest7seg(void) {
    
    showChar7seg('7',1);
    xie_wait_1ms(); 
    showChar7seg('A',0);
    xie_wait_1ms();
}

