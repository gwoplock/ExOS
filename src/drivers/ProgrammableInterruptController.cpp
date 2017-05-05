/*
 * ProgrammableInterruptController.cpp
 *
 *  Created on: Mar 1, 2017
 *      Author: garrett
 */

#include "ProgrammableInterruptController.h"

ProgrammableInterruptController pics[] = {ProgrammableInterruptController(false), ProgrammableInterruptController(true)};

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
	outb(port+DATA_OFFSET, MODE_8086);
	io_wait();
	outb(port+DATA_OFFSET, mask);
}

void ProgrammableInterruptController::setMask(uint8_t line) {
	mask = inb(port+DATA_OFFSET) | (1<<line);
	outb(port+DATA_OFFSET, mask);
}

void ProgrammableInterruptController::unMask(uint8_t line) {
	mask = inb(port+DATA_OFFSET) & ~(1<<line);
	outb(port+DATA_OFFSET, mask);
}

void ProgrammableInterruptController::sendEndOfInterrupt(uint8_t line) {
	outb(port, EOI_COMMAND);
}

void sendEOI(uint8_t line){
	if (line < 8){
		pics[0].sendEndOfInterrupt(line);
	} else {
		pics[1].sendEndOfInterrupt(line-8);
	}
}

void unMaskIrq(uint8_t line){
	if (line < 8){
		pics[0].unMask(line);
	} else {
		pics[1].unMask(line-8);
	}
}

void maskIrq(uint8_t line){
	if (line < 8){
		pics[0].setMask(line);
	} else {
		pics[1].setMask(line-8);
	}
}

void picRemap(uint8_t masterOffset, uint8_t slaveOffset){
	pics[0].remap(masterOffset);
	pics[1].remap(slaveOffset);
	outb(0x21, 4);
	outb(0xA1, 2);
}
