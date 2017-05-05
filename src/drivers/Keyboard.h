/*
 * Keyboard.h
 *
 *  Created on: May 5, 2017
 *      Author: garrett
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

enum SCAN_CODE{
	SET_1, SET_2, SET_3
};

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
	public:
		Keyboard( );
		Keyboard(SCAN_CODE scanCode);
};

#endif /* KEYBOARD_H_ */
