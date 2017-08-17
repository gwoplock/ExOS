/*
 * Console.h
 *
 *  Created on: May 5, 2017
 *      Author: garrett
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "../global.h"


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

enum VgaColor {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint16_t vgaEntry(unsigned char _charToBePrinted, uint8_t _Color) {
	return (uint16_t) _charToBePrinted | (uint16_t) _Color << 8;
}

static inline uint8_t vgaEntryColor(enum VgaColor _fg, enum VgaColor _bg) {
	return _fg | _bg << 4;
}

void terminalInit(uint16_t* bufferstart);

void terminalSetColor(uint8_t _Color);

void terminalPutEntryAt(char c, uint8_t _Color, size_t x, size_t y);

void terminalPutChar(char c);

void terminalWrite(const char* data, size_t size);

size_t stringLength(const char* str);

void terminalWriteString(const char* data);

void terminalHandleSpecialKey(char _specalChar, uint16_t* mods);

void teminalUpdateBar(int row, int col);

void terminalScroll( );

void writeInt(uint64_t num);




#endif /* CONSOLE_H_ */
