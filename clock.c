/*
 * clock_calibration.c
 *
 *  Documentation: I referenced C2C Buscho's code for help
 */

#include "clock.h"
#include "msp430.h"

void clockSet_1MHz(){
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_1MHZ;                // Set clockspeed to 1MHZ
        DCOCTL = CALDCO_1MHZ;
}

void clockSet_8MHZ(){
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_8MHZ;                // Set clockspeed to 8MHZ
        DCOCTL = CALDCO_8MHZ;
}

void clockSet_12MHZ(){
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_12MHZ;                // Set clockspeed to 12MHZ
        DCOCTL = CALDCO_12MHZ;
}

void clockSet_16MHZ(){
        DCOCTL = 0x00;
        BCSCTL1 = CALBC1_16MHZ;                // Set clockspeed to 16MHZ
        DCOCTL = CALDCO_16MHZ;
}

