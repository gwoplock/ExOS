/*
 * ProgrammableInterruptController.cpp
 *
 *  Created on: Mar 1, 2017
 *      Author: garrett
 */

#include "ProgrammableInterruptController.h"

/*ProgrammableInterruptController pics[] = {ProgrammableInterruptController(false), ProgrammableInterruptController(true)};
buildPics(){

}
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
	BREAKPOINT
	outb(port, EOI_COMMAND);
}

void sendEOI(uint8_t line){
	if (line < 8){
		pics[0].sendEndOfInterrupt(line);
	} else {
		pics[0].sendEndOfInterrupt(line);
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
}*/

void PIC_sendEOI(unsigned char irq) {
	if (irq >= 8)
		outb(PIC2_COMMAND, PIC_EOI);

	outb(PIC1_COMMAND, PIC_EOI);
}

void IRQ_set_mask(unsigned char IRQline) {
	uint16_t port;
	uint8_t value;

	if (IRQline < 8 + 0x20) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		IRQline -= 8;
	}
	value = inb(port) | (1 << IRQline);
	outb(port, value);
}

void IRQ_clear_mask(unsigned char IRQline) {
	uint16_t port;
	uint8_t value;

	if (IRQline < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		IRQline -= 8;
	}
	value = inb(port) & ~ (1 << (IRQline + 0x20));
	outb(port, value);
}

void PIC_remap(int offset1, int offset2)
{
	unsigned char a1, a2;

	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();

	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	outb(PIC1_DATA, a1);   // restore saved masks.
	outb(PIC2_DATA, a2);
}
