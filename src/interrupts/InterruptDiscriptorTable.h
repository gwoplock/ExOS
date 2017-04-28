/*
 * InterruptDiscriptorTable.h
 *
 *  Created on: Feb 27, 2017
 *      Author: garrett
 */

#ifndef INTERRUPTDISCRIPTORTABLE_H_
#define INTERRUPTDISCRIPTORTABLE_H_

#include "../global.h"
#include "../drivers/ProgrammableInterruptController.h"

struct IdtEntry {
		uint16_t offset_1; // offset bits 0..15
		uint16_t selector; // a code segment selector in GDT or LDT
		uint8_t zero;      // unused, set to 0
		uint8_t type_attr; // type and attributes, see below
		uint16_t offset_2; // offset bits 16..31F
}__attribute__((__packed__));

struct IdtDiscriptor {
		uint16_t size;
		uint32_t offset;
};

//possible should be void ____()
extern void* isr_0;
extern void* isr_1;
extern void* isr_2;
extern void* isr_3;
extern void* isr_4;
extern void* isr_5;
extern void* isr_6;
extern void* isr_7;
extern void* isr_8;
extern void* isr_9;
extern void* isr_10;
extern void* isr_11;
extern void* isr_12;
extern void* isr_13;
extern void* isr_14;
extern void* isr_15;
extern void* isr_16;
extern void* isr_17;
extern void* isr_18;
//--------------------------------------------
extern void* irq_0;
extern void* irq_1;
extern void* irq_2;
extern void* irq_3;
extern void* irq_4;
extern void* irq_5;
extern void* irq_6;
extern void* irq_7;
extern void* irq_8;
extern void* irq_9;
extern void* irq_10;
extern void* irq_11;
extern void* irq_12;
extern void* irq_13;
extern void* irq_14;
extern void* irq_15;

class InterruptDiscriptorTable {
	private:
		size_t size;
		IdtEntry idt[255];
	public:

		IdtEntry encode(uint32_t offset, uint16_t selector);
		void load( ) {
			//get the size of the IDT. -1 is x86 BULLSHIT
			size_t sizeOfidt = (size * sizeof(IdtEntry)) - 1;
			//build descriptor. no i cant spell
			static IdtDiscriptor idtd;
			idtd.offset = (uint32_t) idt;
			idtd.size = sizeOfidt;
			//send the mem address to asm. tell cpu where IDT is
			asm ("LIDT %[idt]" : : [idt] "m" (idtd));
		}
		InterruptDiscriptorTable( );
};

#endif /* INTERRUPTDISCRIPTORTABLE_H_ */
