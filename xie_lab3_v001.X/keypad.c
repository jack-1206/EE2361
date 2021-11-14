/*
 * File:   keypad.c
 * Author: xieruide
 *
 * Created on June 24, 2020, 1:19 PM
 */


#include "xc.h"
#include "keypad.h"
#include "delay.h"

void initKeyPad(void){
    setup();
    TRISA |= 0b0000000000001111;
    TRISB |= 0b0000000000000011;
    CNPU1bits.CN2PUE=1;
    CNPU1bits.CN3PUE=1;
    CNPU2bits.CN30PUE=1;
    CNPU2bits.CN29PUE=1;
}

int column(void){
    int a=PORTA;
    int col;
    a&=0xf;
    if(a==0b0111){
        col=0;
    }else if(a==0b1011){
        col=1;
    }else if(a==0b1101){
        col=2;
    }else if(a==0b1110){
        col=3;
    }else{
        col=-1;
    }
    return col;
}

char readKeyPadRAW(void){
    char keyArray[]={'1','2','3','A','4','5','6','b','7','8','9','C','E','0','F','d'};
    int rowAct[4]={0xe000,0xd000,0xb000,0x7000};
    int row;
    int col,keyIndex;
    for(row=0;row<4;row++){
        LATB&=0x0fff;
        LATB|=rowAct[row];
        xie_wait_50us();//debounce
        col=column();
        if(col!=-1){
            break;
        }
    }
    if(col==-1){
        return 'n';
    }else{
        keyIndex=row*4+col;
        return keyArray[keyIndex];
    }
}