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

extern ProgrammableInterruptController pics[];

void picRemap(uint8_t masterOffset, uint8_t slaveOffset);

void maskIrq(uint8_t line);

void unMaskIrq(uint8_t line);

void sendEOI(uint8_t line);

#endif /* PROGRAMMABLEINTERRUPTCONTROLLER_H_ */
