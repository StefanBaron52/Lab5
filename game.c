/* game.c - Lab 5 - A Simple Game
 *
 * Author: Stefan Baron von Vietinghoff-Scheel, USAF
 *
 * Function: This is the source file of the Lab 5 - A Simple Game.
 * The source file holds the bulk of the code where we program the
 * MSP430 what to do. It includes the header file as well as calling on
 * the main.c file to write strings and characters to the LCD.
 *
 * Documentation: Day 1: I referenced my Lab 4 code to get a quick start
 * on the Lab 5 code. I had some good code I wanted to use to clear the LCD
 * as well as write to the LCD. I also referenced Captain Branchflower's code
 * to get a heard start on getting an overall format on how to go about coding.
 *
 */

#include <msp430g2553.h>
#include "game.h"
#include "lcd.h"

unsigned char initPlayer() {
	return 0x80;           //Starting position of the player on top left of LCD screen
}

void printPlayer(unsigned char player) {
	writeCommandByte(player);
	writeDataByte('*');   //This is what we print for the player, the star is represented as the player
}

void clearPlayer(unsigned char player) {
	writeCommandByte(player);
	writeDataByte(' ');   //This puts a space in the point where the player used to be
}

unsigned char movePlayer(unsigned char player, unsigned char direction) {
	clearPlayer(player);

	switch (direction)
	{
		case UP:
			player &= ~BIT6;								//clear bit6
			break;
		case DOWN:
			player |= BIT6;
			break;
		case RIGHT:
			if ((player & 0x0f) < 7)			//if the player is greater than top left, but less than the
				player++;									//end position
			break;
		case LEFT:
			if ((player & 0x0f) > 0)
				player--;
			break;
	}

	printPlayer(player);								//need to print the player
	return player;
}

char didPlayerWin(unsigned char player) {
	return player == 0xC7;								//did the player reach the bottom right corner of screen?
}

