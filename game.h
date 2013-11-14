/*
 * game.h
 *
 *  Created on: Nov 5, 2013
 *      Author: C15Stefan.BaronvonVi
 */

#ifndef GAME_H_
#define GAME_H_



#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define ROW_MASK 0x40

#define NUM_MINES 2



unsigned char initPlayer();


void printPlayer(unsigned char player);   //prints the player to the screen


void clearPlayer(unsigned char player);   //clears the player from previous location


unsigned char movePlayer(unsigned char player, unsigned char direction);    //moves the player in direction specified


char didPlayerWin(unsigned char player);  //tests to see if the player won



#endif /* GAME_H_ */
