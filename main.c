/* main.c - Lab 5 - A Simple Game
 *
 * Author: Stefan Baron von Vietinghoff-Scheel, USAF
 *
 * Function: Implements a function of the game. The game, a moving character
 * represented by an (*), will move across the 8 frame LCD screen on the
 * geek box in order to make it to the bottom right corner to essentially win
 * the game. In order to lose the game, the player takes either more than 2 seconds
 * for Required and "B" functionality or runs into a randomly placed mine (X) for "A"
 * functionality. Using push buttons 1-4, the user will be able to navigate across
 * the screen and avoid mines. The main.c file will include functions listed in
 * the header file as well as writing to the LCD screen. Strings are important
 * part of this file.
 *
 * Documentation: Day 1: I referenced Captain Branchflower's Code for help on getting
 * started with the code.
 */

#include <msp430.h>
#include "game.h"
#include "button.h"
#include "lcd.h"
#include "button.h"
#include "clock.h"

//I decided to go about using this pethod of declaring functions. We learned it the first few C lessons in class
//This helps to keep things better organized in my code.

void init_timer();
void init_buttons();
void movingPlayer(char buttonToTest);
void Reset(char buttonToTest);

char btnPush = 0;
char timerCount = 0;
char player = 0;
char gameover = 0;

void clearTimer() {
	timerCount = 0;				//set the timer count to 0 when timer is cleared
	TACTL |= TACLR;					//Clear Timer A Register
}

int main(void) {
	WDTCTL = (WDTPW | WDTHOLD);

	player = initPlayer();		//initialize the player
	initSPI();					//The next lines of code are needed to print to screen
	LCDinit();
	LCDclear();
	printPlayer(player);		//print the player on the screen
	init_timer();				//initialize the timer
	init_buttons();				//initialize buttons
	__enable_interrupt();		//enable maskable interrupt

	while (1) {
		if (player == 0xC7) {
			TACTL &= ~TAIE;			//enable interrupt
			LCDclear();				//we want to clear the LCD so the win message is displayed
			cursorToLineOne();		//line of code from Lab 4, writes strings to the LCD
			writeString("YOU");
			cursorToLineTwo();
			writeString("WON!");
			gameover = 1;			//now the game is over so set to 1,
			_delay_cycles(100000);

		}
		if (timerCount >= 4) {
			TACTL &= ~TAIE;			//enable interrupt
			LCDclear();
			cursorToLineOne();
			writeString("Game");	//displays Game Over! on the LCD once the game is lost
			cursorToLineTwo();
			writeString("Over!");
			gameover = 1;			//game is over to set to 1
			_delay_cycles(100000);

		}
	}

	return 0;
}

void init_timer() {
	TACTL &= ~(MC1 | MC0);

	TACTL |= TACLR;				//clear the timer A register
	clockSet_1MHz(); 			//set the speed to 1MHz was is seen in the family users guide
	TACTL |= TASSEL1;
	TACTL |= ID1 | ID0;
	TACTL &= ~TAIFG;
	TACTL |= MC1;
	TACTL |= TAIE;
}

void init_buttons() {
	configureP1PinAsButton(BIT1);			//initializing the buttons, Bits1-4 will be the buttons on P1
	configureP1PinAsButton(BIT2);
	configureP1PinAsButton(BIT3);
	configureP1PinAsButton(BIT4);
	P1IES |= BIT1 | BIT2 | BIT3 | BIT4;
	P1IFG &= ~BIT1 | BIT2 | BIT3 | BIT4;
	P1IE |= BIT1 | BIT2 | BIT3 | BIT4;
}

void testAndRespondToButtonPush(char buttonToTest) {
	if (buttonToTest & P1IFG) {
		if (buttonToTest & P1IES) {
			movingPlayer(buttonToTest);
			clearTimer();
		} else {
			debounce();
		}
		P1IES ^= buttonToTest;
		P1IFG &= ~buttonToTest;
	}
}

void movingPlayer(char buttonToTest) {
	switch (buttonToTest) {
		case BIT1:
			player = movePlayer(player, RIGHT);
			break;
		case BIT2:
			player = movePlayer(player, LEFT);
			break;
		case BIT3:
			player = movePlayer(player, UP);
			break;
		case BIT4:
			player = movePlayer(player, DOWN);
	}
}

void Reset(char buttonToTest) {
	if (buttonToTest & P1IFG) {
		if (buttonToTest & P1IES) {
			gameover = 0;
			LCDclear();
			player = initPlayer();
			printPlayer(player);
			clearTimer();
			TACTL |= TAIE;
		} else {
			debounce();
		}
		P1IES ^= buttonToTest;
		P1IFG &= ~buttonToTest;
	}
}

#pragma vector= TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR() {
	TACTL &= ~TAIFG;
	timerCount++;
}

#pragma vector = PORT1_VECTOR
__interrupt void PORT_1_ISR() {
	if (gameover == 0) {
		testAndRespondToButtonPush(BIT1);
		testAndRespondToButtonPush(BIT2);
		testAndRespondToButtonPush(BIT3);
		testAndRespondToButtonPush(BIT4);
	} else {
		Reset(BIT1);
		Reset(BIT2);
		Reset(BIT3);
		Reset(BIT4);
	}
}

