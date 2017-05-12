/*
 * Keyboard.h
 *
 *  Created on: May 5, 2017
 *      Author: garrett
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "../global.h"

enum SCAN_CODE{
	SET_1, SET_2, SET_3
};

static const char keySet1[] =
		{
				//'\0' /*unused*/, '\0' /*L GUI*/, '\0' /*R CTRL*/, '\0' /*R GUI*/, '\0' /*R ALT*/, '\0' /*APPS*/, '\0' /*PRNT SCRN*/, '\0' /*PAUSE*/, '\0' /*INSERT*/, '\0' /*HOME*/, '\0' /*PG UP*/, '\0' /*DELETE*/, '\0' /*END*/, '\0' /*PG DN*/, '\0' /*U ARROW*/, '\0' /*L ARROW*/, '\0' /*D ARROW*/, '\0' /*R ARROW*/, '\0' /*KP /*/, '\0' /*KP EN*/, /*multi scancode, not in correct place in array*/
				'\0'/*unused*/, '\0' /*ESC*/, '1', '2', '3', '4', '5', '6', '7',
				'8', '9', '0', '-', '=', '\0' /*BKSP*/, '\0' /*TAB*/, 'q', 'w',
				'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
				'\0' /*ENTER*/, '\0' /*L CTRL*/, 'a', 's', 'd', 'f', 'g', 'h',
				'j', 'k', 'l', ';', '\'', '`', '\0' /*L SHFT*/, '\\', 'z', 'x',
				'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\0' /*R SHFT*/,
				'\0' /*KP **/, '\0' /*L ALT*/, ' ' /*SPACE*/, '\0' /*CAPS*/,
				'\0' /*F1*/, '\0' /*F2*/, '\0' /*F3*/, '\0' /*F4*/, '\0' /*F5*/,
				'\0' /*F6*/, '\0' /*F7*/, '\0' /*F8*/, '\0' /*F9*/,
				'\0' /*F10*/, '\0' /*NUM*/, '\0' /*SCROLL*/, '\0' /*KP 7*/,
				'\0' /*KP 8*/, '\0' /*KP 9*/, '\0' /*KP -*/, '\0' /*KP 4*/,
				'\0' /*KP 5*/, '\0' /*KP 6*/, '\0' /*KP +*/, '\0' /*KP 1*/,
				'\0' /*KP 2*/, '\0' /*KP 3*/, '\0' /*KP 0*/, '\0' /*KP .*/,
				'\0' /*unused*/, '\0' /*unused*/, '\0' /*unused*/, '\0' /*F11*/,
				'\0' /*F12*/, };

static const char keySet1Upper[] =
		{
				//'\0' /*unused*/, '\0' /*L GUI*/, '\0' /*R CTRL*/, '\0' /*R GUI*/, '\0' /*R ALT*/, '\0' /*APPS*/, '\0' /*PRNT SCRN*/, '\0' /*PAUSE*/, '\0' /*INSERT*/, '\0' /*HOME*/, '\0' /*PG UP*/, '\0' /*DELETE*/, '\0' /*END*/, '\0' /*PG DN*/, '\0' /*U ARROW*/, '\0' /*L ARROW*/, '\0' /*D ARROW*/, '\0' /*R ARROW*/, '\0' /*KP /*/, '\0' /*KP EN*/, /*multi scancode, not in correct place in array*/
				'\0'/*unused*/, '\0' /*ESC*/, '!', '@', '#', '$', '%', '^', '&',
				'*', '(', ')', '_', '+', '\0' /*BKSP*/, '\0' /*TAB*/, 'Q', 'W',
				'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
				'\0' /*ENTER*/, '\0' /*L CTRL*/, 'A', 'S', 'D', 'F', 'G', 'H',
				'J', 'K', 'L', ':', '"', '~', '\0' /*L SHFT*/, '|', 'Z', 'X',
				'C', 'V', 'B', 'N', 'M', '<', '>', '?', '\0' /*R SHFT*/,
				'\0' /*KP **/, '\0' /*L ALT*/, ' ' /*SPACE*/, '\0' /*CAPS*/,
				'\0' /*F1*/, '\0' /*F2*/, '\0' /*F3*/, '\0' /*F4*/, '\0' /*F5*/,
				'\0' /*F6*/, '\0' /*F7*/, '\0' /*F8*/, '\0' /*F9*/,
				'\0' /*F10*/, '\0' /*NUM*/, '\0' /*SCROLL*/, '\0' /*KP 7*/,
				'\0' /*KP 8*/, '\0' /*KP 9*/, '\0' /*KP -*/, '\0' /*KP 4*/,
				'\0' /*KP 5*/, '\0' /*KP 6*/, '\0' /*KP +*/, '\0' /*KP 1*/,
				'\0' /*KP 2*/, '\0' /*KP 3*/, '\0' /*KP 0*/, '\0' /*KP .*/,
				'\0' /*unused*/, '\0' /*unused*/, '\0' /*unused*/, '\0' /*F11*/,
				'\0' /*F12*/, };

enum ModKeyMasks{
	L_CONTROL = 1,
	L_SUPER = 1 << 1,
	L_ALT = 1 << 2,
	L_SHIFT = 1 << 3,
	CAPS_LOCK = 1 << 4,
	R_CONTROL = 1 << 5,
	R_SUPER = 1 << 6,
	R_ALT = 1 << 7,
	R_SHIFT = 1 << 8,
	SCROLL_LOCK = 1 << 9,
	NUM_LOCK = 1 << 10,
};

class Keyboard {
	private:
		SCAN_CODE scanCodeSet;
		uint16_t modKeys = 0;
		static const uint8_t PORT = 0x60;
	public:
		Keyboard( );
		Keyboard(SCAN_CODE scanCode);
		uint8_t getScancode();
		uint8_t getKey(){
			return getKey(modKeys);
		}
		uint8_t getKey(uint8_t scancode){
			return getKey(scancode, modKeys);
		}
		uint8_t getKey(uint16_t modKeys);
		uint8_t getKey(uint8_t _scanCode, uint16_t modKeys);
		uint16_t* getModkeys(){
			return &modKeys;
		}
};

#endif /* KEYBOARD_H_ */
