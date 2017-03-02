/*
 * ProgrammableInterruptController.cpp
 *
 *  Created on: Mar 1, 2017
 *      Author: garrett
 */

#include "ProgrammableInterruptController.h"

ProgrammableInterruptController::ProgrammableInterruptController( ) {
	ProgrammableInterruptController(false);
}

ProgrammableInterruptController::ProgrammableInterruptController(bool slave) {
	if (!slave){
		port = 0x20;
	} else {
		port = 0xA0;
	}
}

void ProgrammableInterruptController::remap(uint8_t offset) {
	uint8_t mask = inb(port+DATA_OFFSET);
	outb(port, INIT_COMMAND);
	io_wait();
	outb(port+DATA_OFFSET, offset);
	io_wait();
	outb(port+DATA_OFFSET, 8086_MODE);
	io_wait();
	outb(port+DATA_OFFSET, mask);
}

void ProgrammableInterruptController::setMask(uint8_t line) {
	mask = inb(port+DATA_OFFSET) | (1<<line);
	outb(port+DATA_OFFSET, mask);
}

void ProgrammableInterruptController::clearMask(uint8_t line) {
	mask = inb(port+DATA_OFFSET) & ~(1<<line);
	outb(port+DATA_OFFSET, mask);
}

void ProgrammableInterruptController::sendEndOfInterrupt(uint8_t line) {
	outb(port, EOI_COMMAND);
}
