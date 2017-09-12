/*
 * ProgrammableInterruptController.h
 *
 *  Created on: Mar 1, 2017
 *      Author: garrett
 */

#ifndef PROGRAMMABLEINTERRUPTCONTROLLER_H_
#define PROGRAMMABLEINTERRUPTCONTROLLER_H_

#include "Global.h"


/*
class ProgrammableInterruptController {
	private:
		uint16_t port = 0x20;
		const uint8_t DATA_OFFSET = 1;
		const uint8_t INIT_COMMAND = 0x11;
		const uint8_t MODE_8086 = 0x01;
		const uint8_t EOI_COMMAND = 0x20;
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

void sendEOI(uint8_t line);*/


#define PIC_EOI		0x20		/* End-of-interrupt command code */
#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

void PICSendEOI(unsigned char irq);

void IRQClearMask(unsigned char IRQline);

void IRQSetMask(unsigned char IRQline);

void PICRemap(int offset1, int offset2);


#endif /* PROGRAMMABLEINTERRUPTCONTROLLER_H_ */
