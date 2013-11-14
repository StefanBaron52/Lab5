/*
 * lcd.h
 *
 *  Created on: Oct 22, 2013
 *      Author: C2C Stefan Baron von Vietinghoff-Scheel
 */

#ifndef LCD_H_
#define LCD_H_

void initSPI();

void LCDinit();

void LCDclear();

void cursorToLineOne();

void cursorToLineTwo();

void writeChar(char asciiChar);

void writeString(char *string);

void scrollString(char* string1, char* string2);

void writeDataByte(char dataByte);

void writeCommandNibble(char commandNibble);

void writeCommandByte(char commandByte);

void LCD_write_8(char byteToSend);

void LCD_write_4(char byteToSend);

void SPI_send(char byteToSend);void SPI_send(char byteToSend);

#endif /* LCD_H_ */

