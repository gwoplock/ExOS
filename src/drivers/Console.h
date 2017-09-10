/*
 * Console.h
 *
 *  Created on: May 5, 2017
 *      Author: garrett
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "../global.h"

/**
 * Dimensions of the VGA console
 */
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

/**
 * codes for VGA colors
 */
enum VgaColor {
	VGA_COLOR_BLACK = 0,         //!< VGA_COLOR_BLACK
	VGA_COLOR_BLUE = 1,          //!< VGA_COLOR_BLUE
	VGA_COLOR_GREEN = 2,         //!< VGA_COLOR_GREEN
	VGA_COLOR_CYAN = 3,          //!< VGA_COLOR_CYAN
	VGA_COLOR_RED = 4,           //!< VGA_COLOR_RED
	VGA_COLOR_MAGENTA = 5,       //!< VGA_COLOR_MAGENTA
	VGA_COLOR_BROWN = 6,         //!< VGA_COLOR_BROWN
	VGA_COLOR_LIGHT_GREY = 7,    //!< VGA_COLOR_LIGHT_GREY
	VGA_COLOR_DARK_GREY = 8,     //!< VGA_COLOR_DARK_GREY
	VGA_COLOR_LIGHT_BLUE = 9,    //!< VGA_COLOR_LIGHT_BLUE
	VGA_COLOR_LIGHT_GREEN = 10,  //!< VGA_COLOR_LIGHT_GREEN
	VGA_COLOR_LIGHT_CYAN = 11,   //!< VGA_COLOR_LIGHT_CYAN
	VGA_COLOR_LIGHT_RED = 12,    //!< VGA_COLOR_LIGHT_RED
	VGA_COLOR_LIGHT_MAGENTA = 13,    //!< VGA_COLOR_LIGHT_MAGENTA
	VGA_COLOR_LIGHT_BROWN = 14,  //!< VGA_COLOR_LIGHT_BROWN
	VGA_COLOR_WHITE = 15,        //!< VGA_COLOR_WHITE
};

/**
 * encode an entry for VGA display
 * @param char to be printed
 * @param color code
 * @return VGA entry
 */
static inline uint16_t vgaEntry(unsigned char _charToBePrinted,
		uint8_t _Color) {
	return (uint16_t) _charToBePrinted | (uint16_t) _Color << 8;
}
/**
 * sets the FG and BG color
 * @param fg color
 * @param bg color
 * @return color fully encoded
 */
static inline uint8_t vgaEntryColor(enum VgaColor _fg, enum VgaColor _bg) {
	return _fg | _bg << 4;
}
/**
 * clears the screen with \0 and sets the start point. also sets the blinking bar and colors.
 * @param bufferStart - where the mem mapped terminal is
 */
void terminalInit(uint16_t* bufferstart);
/**
 * sets the FG and BG colors of the terminal
 * @param color code
 */
void terminalSetColor(uint8_t _Color);
/**
 *  fully encode char and place in the buffer
 * @param the char to print
 * @param the color code
 * @param X Pos
 * @param Y Pos
 */
void terminalPutEntryAt(char c, uint8_t _Color, size_t x, size_t y);
/**
 * put char at next location
 * @param char to print
 */
void terminalPutChar(char c);
/**
 * print a string of known length
 * @param string to print
 * @param length
 */
void terminalWrite(const char* data, size_t size);
/**
 * get string length
 * @param string
 * @return length
 */
size_t stringLength(const char* str);
/**
 * print string of unknown length
 * @param string to print
 */
void terminalWriteString(const char* data);
/**
 * print string of unknown length
 * move to the next line when done
 * @param string to print
 */
void terminalWriteLine(const char* _toPrint);
/**
 * process special keys
 * @param what char to handle
 * @param pointer to modkey flags
 */
void terminalHandleSpecialKey(char _specalChar, uint16_t* mods);
/** move the blinking bar to the proper location
 * @param row
 * @param col
 */
void teminalUpdateBar(int row, int col);
/**
 * handle scrolling up when the last spot is used
 */
void terminalScroll( );
/**
 * Write an integer to the screen in base 10.
 * @param number to print
 */
void writeInt(uint64_t num);
/**
 * Write an integer to the screen converted to the given base (0<b<=36)
 * @param number to print
 * @param base to print as
 */ 
void writeIntBase(uint64_t num, uint64_t base);

#endif /* CONSOLE_H_ */
