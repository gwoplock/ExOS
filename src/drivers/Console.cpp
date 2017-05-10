/*
 * Console.cpp
 *
 *  Created on: May 5, 2017
 *      Author: garrett
 */

#include "Console.h"
#include "../kernel.h"

size_t terminalRow;
size_t terminalColumn;
uint8_t terminalColor;
uint16_t* terminalBuffer;

void terminalInit(uint16_t* bufferStart) {
	//start at the begining
	terminalRow = 0;
	terminalColumn = 0;
	//set color
	terminalColor = vgaEntryColor(VGA_COLOR_LIGHT_BROWN, VGA_COLOR_BLACK);
	//where it is in mem. in the middle because intell still hates you
	terminalBuffer = bufferStart;
	//clear with nulls for backspace and get rid go GRUB's garbage
	for (size_t _y = 0; _y < VGA_HEIGHT; _y++) {
		for (size_t _x = 0; _x < VGA_WIDTH; _x++) {
			const size_t index = _y * VGA_WIDTH + _x;
			terminalBuffer[index] = vgaEntry('\0', terminalColor);
		}
	}
	//set blinky bar at the begining
	teminalUpdateBar(0, 0);
}

void terminalSetColor(uint8_t color) {
	terminalColor = color;
}

//put char at pos with color
void terminalPutEntryAt(char _toPrint, uint8_t _color, size_t _XPos,
		size_t _YPos) {
	const size_t _index = _YPos * VGA_WIDTH + _XPos;
	terminalBuffer[_index] = vgaEntry(_toPrint, _color);
}

//print a char
void terminalPutChar(char _toPrint) {
	terminalPutEntryAt(_toPrint, terminalColor, terminalColumn, terminalRow);
	if ( ++terminalColumn == VGA_WIDTH) {
		terminalColumn = 0;
		if ( ++terminalRow == VGA_HEIGHT) {
			terminalScroll( );
		}
	}
	teminalUpdateBar(terminalRow, terminalColumn);
}

//write a string of known length
void terminalWrite(const char* _toPrint, size_t _length) {
	for (size_t _i = 0; _i < _length; _i++)
		terminalPutChar(_toPrint[_i]);
}

//get a strings length
size_t stringLength(const char* str) {
	size_t _length = 0;
	while (str[_length])
		_length++;
	return _length;
}

//wright string of unknow length
void terminalWriteString(const char* _toPrint) {
	terminalWrite(_toPrint, stringLength(_toPrint));
}

//special keys. they do something
void terminalHandleSpecialKey(char _specalChar, uint16_t* modsLocal) {
	switch (_specalChar) {
		//back space
		case ('\x0E') : {
			size_t _index = 0;
			do {

				if ( --terminalColumn == (size_t) -1) {
					terminalColumn = VGA_WIDTH - 1;
					if ( --terminalRow == (size_t) -1) {
						terminalRow = 0;
						terminalColumn = 0;
						break;
					}
				}
				_index = terminalRow * VGA_WIDTH + terminalColumn;
			} while ( ! (terminalBuffer[_index] & 0xff));
			terminalPutEntryAt('\0', terminalColor, terminalColumn,
					terminalRow);
			teminalUpdateBar(terminalRow, terminalColumn);
			break;
		}
			//tab
		case ('\x0F') : {
			terminalWrite("    ", 4);
			break;
		}
			//enter
		case ('\x1C') : {
			terminalPutChar(' ');
			terminalColumn = 0;
			if ( ++terminalRow == VGA_HEIGHT) {
				terminalScroll( );
			}
			teminalUpdateBar(terminalRow, terminalColumn);
			break;
		}
		case ('\x1D') : {
			*modsLocal |= L_CONTROL;
			break;
		}
		case ('\x2A') : {
			*modsLocal |= L_SHIFT;
			break;
		}
		case ('\x36') : {
			*modsLocal |= R_SHIFT;
			break;
		}
		case ('\x38') : {
			*modsLocal |= L_ALT;
			break;
		}
		case ('\x3A') : {
			*modsLocal ^= CAPS_LOCK;
			break;
		}
		case ('\x45') : {
			*modsLocal ^= NUM_LOCK;
			break;
		}
		case ('\x46') : {
			*modsLocal ^= SCROLL_LOCK;
			break;
		}
		case ('\x9D') : {
			*modsLocal &= ~L_CONTROL;
			break;
		}
		case ('\xAA') : {
			*modsLocal &= ~L_SHIFT;
			break;
		}
		case ('\xB6') : {
			*modsLocal &= ~R_SHIFT;
			break;
		}
	}
}
//move that blinky line
void teminalUpdateBar(int row, int col) {
	unsigned short position = (row * VGA_WIDTH) + col;
	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char) (position & 0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char) ( (position >> 8) & 0xFF));
}

//scroll up when out of room
void terminalScroll( ) {
	terminalRow = VGA_HEIGHT - 1;
	memcpy((void*) (0xB8000 + (uint32_t)(pageTable.getKernelStart( ))),
			(void*) (0xb8000 + (uint32_t)(pageTable.getKernelStart( ))
					+ VGA_WIDTH * 2), (VGA_WIDTH * 2) * (VGA_HEIGHT - 1));
	memSet(
			(void*) (0xB8000 + (uint32_t)(pageTable.getKernelStart( ))
					+ (VGA_WIDTH * 2) * (VGA_HEIGHT - 1)), VGA_WIDTH * 2, '\0');
}

//write a number (backwards because i hate you)
void writeInt(uint64_t num) {
	uint8_t out[20];
	for (int i = 0; i < 20; i++) {
		out[i] = '\0';
	}
	if ( !num) {
		terminalPutChar('0');
		return;
	}

	int n = 19;
	while (n>=0 && num != 0) {
		out[n] = ('0' + (num % 10));
		num /= 10;
		n--;
	}
	terminalWrite((const char *)out, 20);
}


