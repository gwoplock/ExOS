/*
 * ProgrammableInterruptController.h
 *
 *  Created on: Mar 1, 2017
 *      Author: garrett
 */

#ifndef PROGRAMMABLEINTERRUPTCONTROLLER_H_
#define PROGRAMMABLEINTERRUPTCONTROLLER_H_

#include "../global.h"



class ProgrammableInterruptController {
	private:
		uint16_t port;
		const uint8_t DATA_OFFSET = 1;
		const uint8_t INIT_COMMAND = 0x11;
		const uint8_t MODE_8086 = 0x01;
		//TODO make real value
		const uint8_t EOI_COMMAND = 0x0;
		uint8_t mask;
	public:
		ProgrammableInterruptController();
		ProgrammableInterruptController(bool slave);
		void remap(uint8_t offset);
		void setMask(uint8_t line);
		void unMask(uint8_t line);
		void sendEndOfInterrupt(uint8_t line);
};

ProgrammableInterruptController pics[] = {ProgrammableInterruptController(false), ProgrammableInterruptController(true)};
void picRemap(uint8_t masterOffset, uint8_t slaveOffset){
	pics[0].remap(masterOffset);
	pics[1].remap(slaveOffset);
	outb(0x21, 4);
	outb(0xA1, 2);
}
void maskIrq(uint8_t line){
	if (line < 8){
		pics[0].setMask(line);
	} else {
		pics[1].setMask(line-8);
	}
}

void unMaskIrq(uint8_t line){
	if (line < 8){
		pics[0].unMask(line);
	} else {
		pics[1].unMask(line-8);
	}
}

void sendEOI(uint8_t line){
	if (line < 8){
		pics[0].sendEndOfInterrupt(line);
	} else {
		pics[1].sendEndOfInterrupt(line-8);
	}
}

#endif /* PROGRAMMABLEINTERRUPTCONTROLLER_H_ */
