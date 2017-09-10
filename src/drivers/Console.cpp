/*
 * Console.cpp
 *
 *  Created on: May 5, 2017
 *      Author: garrett
 */

#include "Console.h"
#include "../kernel.h"
#include "Keyboard.h"
#include "../memory/structures/PageTable.h"
#include "../memory/mem.h"

/**
 * Function prototype for the internal use newline()
 */
void newline();

/**
 * current terminal row
 */
size_t terminalRow;
/**
 * current terminal column
 */
size_t terminalColumn;
/**
 * the color code we are using
 */
uint8_t terminalColor;
/**
 * the address of the start of the terminal
 */
uint16_t* terminalBuffer;

/**
 * clears the screen with \0 and sets the start point. also sets the blinking bar and colors.
 * @param bufferStart - where the mem mapped terminal is
 */
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
/**
 * sets the FG and BG colors of the terminal
 * @param color code
 */
void terminalSetColor(uint8_t color) {
	terminalColor = color;
}

/**
 *  fully encode char and place in the buffer
 * @param the char to print
 * @param the color code
 * @param X Pos
 * @param Y Pos
 */
void terminalPutEntryAt(char _toPrint, uint8_t _color, size_t _XPos,
		size_t _YPos) {
	const size_t _index = _YPos * VGA_WIDTH + _XPos;
    // Handle newlines
    if (_toPrint == 0x0A) {
        newline();
    } else {
	    terminalBuffer[_index] = vgaEntry(_toPrint, _color);
        terminalColumn++;
    }
}

/**
 * put char at next location
 * @param char to print
 */
void terminalPutChar(char _toPrint) {
	terminalPutEntryAt(_toPrint, terminalColor, terminalColumn, terminalRow);
	if (terminalColumn == VGA_WIDTH) {
        newline();
	}
	teminalUpdateBar(terminalRow, terminalColumn);
}

/**
 * print a string of known length
 * @param string to print
 * @param length
 */
void terminalWrite(const char* _toPrint, size_t _length) {
	for (size_t _i = 0; _i < _length; _i++)
		terminalPutChar(_toPrint[_i]);
}

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
/**
 * get string length
 * @param string
 * @return length
 */
size_t strlen(const char* str) {
	size_t _length = 0;
	while (str[_length])
		_length++;
	return _length;
}
#if defined(__cplusplus)
}/* Use C linkage for kernel_main. */
#endif

/**
 * print string of unknown length
 * @param string to print
 */
void terminalWriteString(const char* _toPrint) {
	terminalWrite(_toPrint, strlen(_toPrint));
}

/**
 * print string of unknown length
 * move to the next line when done
 * @param string to print
 */
void terminalWriteLine(const char* _toPrint) {
	terminalWrite(_toPrint, strlen(_toPrint));
    newline();
	teminalUpdateBar(terminalRow, terminalColumn);
}

/**
 * process special keys
 * @param what char to handle
 * @param pointer to modkey flags
 */
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
			teminalUpdateBar(terminalRow, --terminalColumn);
			break;
		}
			//tab
		case ('\x0F') : {
			terminalWrite("    ", 4);
			break;
		}
			//enter
		case ('\x1C') : {
            newline();
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
/**
 * move the blinking bar to the proper location
 * @param row
 * @param col
 */
void teminalUpdateBar(int row, int col) {
	unsigned short position = (row * VGA_WIDTH) + col;
	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char) (position & 0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char) ( (position >> 8) & 0xFF));
}

/**
 * Move the cursor to the next line. Scroll if necessary
 * Internal method, do not include in Console.h
 * If a blank line is needed, use terminalWriteLine() instead
 */
void newline( ) {
    terminalPutChar(' ');
    terminalRow++;
    terminalColumn = 0;
    if (terminalRow == VGA_HEIGHT) {
        terminalScroll();
    }
}
/**
 * handle scrolling up when the last spot is used
 */
void terminalScroll( ) {
	terminalRow = VGA_HEIGHT - 1;
	memcpy((void*) (0xB8000 + (uint32_t)(pageTable.getKernelStart( ))),
			(void*) (0xb8000 + (uint32_t)(pageTable.getKernelStart( ))
					+ VGA_WIDTH * 2), (VGA_WIDTH * 2) * (VGA_HEIGHT - 1));
	memSet(
			(void*) (0xB8000 + (uint32_t)(pageTable.getKernelStart( ))
					+ (VGA_WIDTH * 2) * (VGA_HEIGHT - 1)), VGA_WIDTH * 2, '\0');
}

/**
 * write a number. i think it works right
 * @param number to print
 */
void writeInt(uint64_t num) {
	uint8_t out[21];
	for (int i = 0; i < 21; i++) {
		out[i] = '\0';
	}
	if (!num) {
		terminalPutChar('0');
		return;
	}

	int n = 19;
	while (n>=0 && num != 0) {
		out[n] = ('0' + (num % 10));
		num /= 10;
		n--;
	}

    /* Skip to the first non null char */
    int pos;
    for (pos = 0; !out[pos]; pos++);

	terminalWriteString((const char*)(out + pos));
}
