/*
 * Keyboard.cpp
 *
 *  Created on: May 5, 2017
 *      Author: garrett
 */

#include "Keyboard.h"

Keyboard::Keyboard( ) {

}

uint8_t Keyboard::getScancode( ) {
	uint8_t scanCode = 0;
	//read scan code from the keyboard port
	scanCode = inb(PORT);
	return scanCode;
}

uint8_t Keyboard::getKey(uint16_t modKeys) {
	return getKey(getScancode( ), modKeys);
}

uint8_t Keyboard::getKey(uint8_t scanCode, uint16_t modKeys) {
	//if it should be uppercase, use the uppercae set
	if ( (modKeys & (L_SHIFT | R_SHIFT | CAPS_LOCK)) != 0) {
		return keySet1Upper[scanCode];
	}
	//if not upper, use lower case set
	return keySet1[scanCode];
}
