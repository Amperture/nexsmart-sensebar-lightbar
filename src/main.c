/*
 * ===========================================================================
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
 * ===========================================================================
 */

#include "msp430.h"
#include "uart.h"
#include "spi.h"

/* Defines for 7 Segment Number display Bytes */
#define NUM_SHIFT_REGISTERS     4
#define WATER_STORED            0
#define WATER_USED              1
#define ENERGY_STORED           2
#define ENERGY_USED             3

/* Encoding for the 7-Segment Data 
 *
 *              0   1   2   3   4   5   6   7   8
 *
 *      ENERGY:
 *          Stored:
 *              a   b   c   d   e   f   g   h   i
 *          Consumed:
 *              A   B   C   D   E   F   G   H   I
 *
 *      Water:
 *          Stored:
 *              k   l   m   n   o   p   q   r   s
 *          Consumed:
 *              K   L   M   N   O   P   Q   R   S
 */

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

    // Set up 7-Segment number displays.
    //      0 -- Temperature Tens
    //      1 -- Temperature Ones
    //      2 -- Time Hour Tens
    //      3 -- Time Hour Ones
    //      4 -- Time Minute Tens
    //      5 -- Time Minute Ones
    uint8_t sendBytes[NUM_SHIFT_REGISTERS];
    uint8_t sendBytesActual[NUM_SHIFT_REGISTERS];
    uint8_t sendByteBitMask = 1;
    int sendByteByteMask = 0;

    // Set up 1MHz Clock
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    P1DIR |= BIT3;

    spiInit();
    uartInit();

    uint8_t i = 0;

    while(1){
        //
        //sendBytes[MINUTE_TENS] = SEVEN_SEG_8;
        //

        switch(rxChar){

            //Commands for energy stored.
            case 'a':
                sendBytes[ENERGY_STORED] = 0x00;
                rxChar = 0;
                break;

            case 'b':
                sendBytes[ENERGY_STORED] = 0x01;
                rxChar = 0;
                break;

            case 'c':
                sendBytes[ENERGY_STORED] = 0x03;
                rxChar = 0;
                break;

            case 'd':
                sendBytes[ENERGY_STORED] = 0x07;
                rxChar = 0;
                break;

            case 'e':
                sendBytes[ENERGY_STORED] = 0x0F;
                rxChar = 0;
                break;

            case 'f':
                sendBytes[ENERGY_STORED] = 0x1F;
                rxChar = 0;
                break;

            case 'g':
                sendBytes[ENERGY_STORED] = 0x3F;
                rxChar = 0;
                break;

            case 'h':
                sendBytes[ENERGY_STORED] = 0x7F;
                rxChar = 0;
                break;

            case 'i':
                sendBytes[ENERGY_STORED] = 0xFF;
                rxChar = 0;
                break;

            //Commands for energy used.
            case 'A':
                sendBytes[ENERGY_USED] = 0x00;
                rxChar = 0;
                break;

            case 'B':
                sendBytes[ENERGY_USED] = 0x01;
                rxChar = 0;
                break;

            case 'C':
                sendBytes[ENERGY_USED] = 0x03;
                rxChar = 0;
                break;

            case 'D':
                sendBytes[ENERGY_USED] = 0x07;
                rxChar = 0;
                break;

            case 'E':
                sendBytes[ENERGY_USED] = 0x0F;
                rxChar = 0;
                break;

            case 'F':
                sendBytes[ENERGY_USED] = 0x1F;
                rxChar = 0;
                break;

            case 'G':
                sendBytes[ENERGY_USED] = 0x3F;
                rxChar = 0;
                break;

            case 'H':
                sendBytes[ENERGY_USED] = 0x7F;
                rxChar = 0;
                break;

            case 'I':
                sendBytes[ENERGY_USED] = 0xFF;
                rxChar = 0;
                break;

            //Commands for water stored.
            case 'k':
                sendBytes[WATER_STORED] = 0x00;
                rxChar = 0;
                break;

            case 'l':
                sendBytes[WATER_STORED] = 0x01;
                rxChar = 0;
                break;

            case 'm':
                sendBytes[WATER_STORED] = 0x03;
                rxChar = 0;
                break;

            case 'n':
                sendBytes[WATER_STORED] = 0x07;
                rxChar = 0;
                break;

            case 'o':
                sendBytes[WATER_STORED] = 0x0F;
                rxChar = 0;
                break;

            case 'p':
                sendBytes[WATER_STORED] = 0x1F;
                rxChar = 0;
                break;

            case 'q':
                sendBytes[WATER_STORED] = 0x3F;
                rxChar = 0;
                break;

            case 'r':
                sendBytes[WATER_STORED] = 0x7F;
                rxChar = 0;
                break;

            case 's':
                sendBytes[WATER_STORED] = 0xFF;
                rxChar = 0;
                break;

            //Commands for water used.
            case 'K':
                sendBytes[WATER_USED] = 0x00;
                rxChar = 0;
                break;

            case 'L':
                sendBytes[WATER_USED] = 0x01;
                rxChar = 0;
                break;

            case 'M':
                sendBytes[WATER_USED] = 0x03;
                rxChar = 0;
                break;

            case 'N':
                sendBytes[WATER_USED] = 0x07;
                rxChar = 0;
                break;

            case 'O':
                sendBytes[WATER_USED] = 0x0F;
                rxChar = 0;
                break;

            case 'P':
                sendBytes[WATER_USED] = 0x1F;
                rxChar = 0;
                break;

            case 'Q':
                sendBytes[WATER_USED] = 0x3F;
                rxChar = 0;
                break;

            case 'R':
                sendBytes[WATER_USED] = 0x7F;
                rxChar = 0;
                break;

            case 'S':
                sendBytes[WATER_USED] = 0xFF;
                rxChar = 0;
                break;
        }


        for(i = 0; i < NUM_SHIFT_REGISTERS; ++i){
            //sendBytesActual[i] = 0;
        }

        sendByteBitMask = (sendByteBitMask << 1);
        
        if (sendByteBitMask >= 0x80){
            sendByteBitMask = 1;
            ++sendByteByteMask;
            if (sendByteByteMask == NUM_SHIFT_REGISTERS){
                sendByteByteMask = 0;
            }
        }

        // Set all lights on (Error Check)
        /*
        for(i = 0; i < NUM_SHIFT_REGISTERS; ++i){
            sendBytesActual[i] = 0x0F;
        }
        /**/

        // Code to either send single light at a time, or to send single
        // light per shift register.
        //sendBytesActual[sendByteByteMask] = sendByteBitMask;
        /**/
        for (i = 0; i < NUM_SHIFT_REGISTERS; ++i){
            sendBytesActual[i] = sendBytes[i] & sendByteBitMask;
        } 
        /**/

        for(i = 0; i < NUM_SHIFT_REGISTERS; ++i){
            spiSendChar(sendBytesActual[i]);
        }
        latch595();
    }
}
        
