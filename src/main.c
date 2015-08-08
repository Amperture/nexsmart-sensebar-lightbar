/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Simple Hello World over UART, for testing GDB
 *
 *        Version:  0.0.1
 *        Created:  07/16/2015 10:20:03 PM
 *       Revision:  none
 *       Compiler:  msp430-gcc
 *
 *         Author:  W. Alex Best (mn), alexbest@alexbest.me
 *        Company:  Amperture Engineering
 *
 * =====================================================================================
 */

#include "msp430.h"
#include "uart.h"
#include "spi.h"

unsigned char sendByte;

void latch595(){
    __delay_cycles(20);
    P1OUT |= BIT3;
    __delay_cycles(10);
    P1OUT &= ~BIT3;
    __delay_cycles(10);
}

int main(void){

    //Disable Watchdog
    WDTCTL = WDTPW + WDTHOLD;

    // Set up 1MHz Clock
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    P1DIR |= BIT3;

    spiInit();
    uartInit();


    while(1){
        if (rxChar == '1') {
            sendByte = 0x01;
            rxChar = 0;
        }

        if (rxChar == '2') {
            sendByte = 0x02;
            rxChar = 0;
        }

        spiSendChar(sendByte);
        //spiSendChar(0xAA);
        latch595();
    }
        
}

