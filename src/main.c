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
#define SEVEN_SEG_0 BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5
#define SEVEN_SEG_1 BIT1 + BIT2
#define SEVEN_SEG_2 BIT0 + BIT1 + BIT6 + BIT4 + BIT3
#define SEVEN_SEG_3 BIT0 + BIT1 + BIT2 + BIT3 + BIT6
#define SEVEN_SEG_4 BIT6 + BIT5 + BIT1 + BIT2
#define SEVEN_SEG_5 BIT0 + BIT5 + BIT6 + BIT2 + BIT3
#define SEVEN_SEG_6 BIT0 + BIT5 + BIT4 + BIT3 + BIT2 + BIT6
#define SEVEN_SEG_7 BIT0 + BIT1 + BIT2
#define SEVEN_SEG_8 0xFF
#define SEVEN_SEG_9 BIT0 + BIT5 + BIT6 + BIT1 + BIT2

/* Defines for bytes to send to 7-Segment Shift Registers */
#define NUM_SHIFT_REGISTERS 6
#define TEMPERATURE_TENS 0
#define TEMPERATURE_ONES 1 
#define HOUR_TENS 2
#define HOUR_ONES 3
#define MINUTE_TENS 4
#define MINUTE_ONES 5

/* Encoding for the 7-Segment Data 
 *
 *              0   1   2   3   4   5   6   7   8   9
 *
 *      TEMPERATURE:
 *          Tens:
 *              a   b   c   d   e   f   g   h   i   j
 *          Ones:
 *              A   B   C   D   E   F   G   H   I   J
 *
 *      HOURS:
 *          Tens:
 *              k   l   m   n   o   p   q   r   s   t
 *          Ones:
 *              K   L   M   N   O   P   Q   R   S   T
 *
 *      MINUTES:
 *          Tens:
 *              0   1   2   3   4   5   6   7   8   9 
 *          Ones:
 *              )   !   @   #   $   %   ^   &   *   (
 */

/*
 *  Encoding diagram for the 7-Segments of the display
 *          0
 *          ____
 *          |  | 1
 *        5 |  |
 *          ==== 6
 *        4 |  | 
 *          |  | 2
 *          ====
 *             3
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
    uint8_t sendBytes[6];

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

            //Commands for the tens digit of temperature.
            case 'a':
                sendBytes[TEMPERATURE_TENS] = SEVEN_SEG_0;
                rxChar = 0;
                break;
            case 'b':
                sendBytes[TEMPERATURE_TENS] = SEVEN_SEG_1;
                rxChar = 0;
                break;
            case 'c':
                sendBytes[TEMPERATURE_TENS] = SEVEN_SEG_2;
                rxChar = 0;
                break;
            case 'd':
                sendBytes[TEMPERATURE_TENS] = SEVEN_SEG_3;
                rxChar = 0;
                break;
            case 'e':
                sendBytes[TEMPERATURE_TENS] = SEVEN_SEG_4;
                rxChar = 0;
                break;
            case 'f':
                sendBytes[TEMPERATURE_TENS] = SEVEN_SEG_5;
                rxChar = 0;
                break;
            case 'g':
                sendBytes[TEMPERATURE_TENS] = SEVEN_SEG_6;
                rxChar = 0;
                break;
            case 'h':
                sendBytes[TEMPERATURE_TENS] = SEVEN_SEG_7;
                rxChar = 0;
                break;
            case 'i':
                sendBytes[TEMPERATURE_TENS] = SEVEN_SEG_8;
                rxChar = 0;
                break;
            case 'j':
                sendBytes[TEMPERATURE_TENS] = SEVEN_SEG_9;
                rxChar = 0;
                break;

            //Commands for the ones digit of temperature.
            case 'A':
                sendBytes[TEMPERATURE_ONES] = SEVEN_SEG_0;
                rxChar = 0;
                break;
            case 'B':
                sendBytes[TEMPERATURE_ONES] = SEVEN_SEG_1;
                rxChar = 0;
                break;
            case 'C':
                sendBytes[TEMPERATURE_ONES] = SEVEN_SEG_2;
                rxChar = 0;
                break;
            case 'D':
                sendBytes[TEMPERATURE_ONES] = SEVEN_SEG_3;
                rxChar = 0;
                break;
            case 'E':
                sendBytes[TEMPERATURE_ONES] = SEVEN_SEG_4;
                rxChar = 0;
                break;
            case 'F':
                sendBytes[TEMPERATURE_ONES] = SEVEN_SEG_5;
                rxChar = 0;
                break;
            case 'G':
                sendBytes[TEMPERATURE_ONES] = SEVEN_SEG_6;
                rxChar = 0;
                break;
            case 'H':
                sendBytes[TEMPERATURE_ONES] = SEVEN_SEG_7;
                rxChar = 0;
                break;
            case 'I':
                sendBytes[TEMPERATURE_ONES] = SEVEN_SEG_8;
                rxChar = 0;
                break;
            case 'J':
                sendBytes[TEMPERATURE_ONES] = SEVEN_SEG_9;
                rxChar = 0;
                break;

            //Commands for the tens digit of the hour
            case 'k':
                sendBytes[HOUR_TENS] = SEVEN_SEG_0;
                rxChar = 0;
                break;
            case 'l':
                sendBytes[HOUR_TENS] = SEVEN_SEG_1;
                rxChar = 0;
                break;
            case 'm':
                sendBytes[HOUR_TENS] = SEVEN_SEG_2;
                rxChar = 0;
                break;
            case 'n':
                sendBytes[HOUR_TENS] = SEVEN_SEG_3;
                rxChar = 0;
                break;
            case 'o':
                sendBytes[HOUR_TENS] = SEVEN_SEG_4;
                rxChar = 0;
                break;
            case 'p':
                sendBytes[HOUR_TENS] = SEVEN_SEG_5;
                rxChar = 0;
                break;
            case 'q':
                sendBytes[HOUR_TENS] = SEVEN_SEG_6;
                rxChar = 0;
                break;
            case 'r':
                sendBytes[HOUR_TENS] = SEVEN_SEG_7;
                rxChar = 0;
                break;
            case 's':
                sendBytes[HOUR_TENS] = SEVEN_SEG_8;
                rxChar = 0;
                break;
            case 't':
                sendBytes[HOUR_TENS] = SEVEN_SEG_9;
                rxChar = 0;
                break;

            //Commands for the Ones digit of the Hour
            case 'K':
                sendBytes[HOUR_ONES] = SEVEN_SEG_0;
                rxChar = 0;
                break;
            case 'L':
                sendBytes[HOUR_ONES] = SEVEN_SEG_1;
                rxChar = 0;
                break;
            case 'M':
                sendBytes[HOUR_ONES] = SEVEN_SEG_2;
                rxChar = 0;
                break;
            case 'N':
                sendBytes[HOUR_ONES] = SEVEN_SEG_3;
                rxChar = 0;
                break;
            case 'O':
                sendBytes[HOUR_ONES] = SEVEN_SEG_4;
                rxChar = 0;
                break;
            case 'P':
                sendBytes[HOUR_ONES] = SEVEN_SEG_5;
                rxChar = 0;
                break;
            case 'Q':
                sendBytes[HOUR_ONES] = SEVEN_SEG_6;
                rxChar = 0;
                break;
            case 'R':
                sendBytes[HOUR_ONES] = SEVEN_SEG_7;
                rxChar = 0;
                break;
            case 'S':
                sendBytes[HOUR_ONES] = SEVEN_SEG_8;
                rxChar = 0;
                break;
            case 'T':
                sendBytes[HOUR_ONES] = SEVEN_SEG_9;
                rxChar = 0;
                break;

            // Commands for the Tens Digit of the Minute
            case '0':
                sendBytes[MINUTE_TENS] = SEVEN_SEG_0;
                rxChar = 0;
                break;
            case '1':
                sendBytes[MINUTE_TENS] = SEVEN_SEG_1;
                rxChar = 0;
                break;
            case '2':
                sendBytes[MINUTE_TENS] = SEVEN_SEG_2;
                rxChar = 0;
                break;
            case '3':
                sendBytes[MINUTE_TENS] = SEVEN_SEG_3;
                rxChar = 0;
                break;
            case '4':
                sendBytes[MINUTE_TENS] = SEVEN_SEG_4;
                rxChar = 0;
                break;
            case '5':
                sendBytes[MINUTE_TENS] = SEVEN_SEG_5;
                rxChar = 0;
                break;
            case '6':
                sendBytes[MINUTE_TENS] = SEVEN_SEG_6;
                rxChar = 0;
                break;
            case '7':
                sendBytes[MINUTE_TENS] = SEVEN_SEG_7;
                rxChar = 0;
                break;
            case '8':
                sendBytes[MINUTE_TENS] = SEVEN_SEG_8;
                rxChar = 0;
                break;
            case '9':
                sendBytes[MINUTE_TENS] = SEVEN_SEG_9;
                rxChar = 0;
                break;

             
            // Commands for the Ones Digit of the Minute
            case ')':
                sendBytes[MINUTE_ONES] = SEVEN_SEG_0;
                rxChar = 0;
                break;
            case '!':
                sendBytes[MINUTE_ONES] = SEVEN_SEG_1;
                rxChar = 0;
                break;
            case '@':
                sendBytes[MINUTE_ONES] = SEVEN_SEG_2;
                rxChar = 0;
                break;
            case '#':
                sendBytes[MINUTE_ONES] = SEVEN_SEG_3;
                rxChar = 0;
                break;
            case '$':
                sendBytes[MINUTE_ONES] = SEVEN_SEG_4;
                rxChar = 0;
                break;
            case '%':
                sendBytes[MINUTE_ONES] = SEVEN_SEG_5;
                rxChar = 0;
                break;
            case '^':
                sendBytes[MINUTE_ONES] = SEVEN_SEG_6;
                rxChar = 0;
                break;
            case '&':
                sendBytes[MINUTE_ONES] = SEVEN_SEG_7;
                rxChar = 0;
                break;
            case '*':
                sendBytes[MINUTE_ONES] = SEVEN_SEG_8;
                rxChar = 0;
                break;
            case '(':
                sendBytes[MINUTE_ONES] = SEVEN_SEG_9;
                rxChar = 0;
                break;
        }
        for(i = 0; i < NUM_SHIFT_REGISTERS; i++){
            spiSendChar(sendBytes[i]);
        }
        latch595();
    }
}
        
