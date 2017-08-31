/*
 * InterruptDiscriptorTable.h
 *
 *  Created on: Feb 27, 2017
 *      Author: garrett
 */

#ifndef INTERRUPTDISCRIPTORTABLE_H_
#define INTERRUPTDISCRIPTORTABLE_H_

#include "../global.h"

/**
 * structure used by the cpu to handler interrupts
 */
struct IdtEntry {
		uint16_t offset_1; // offset bits 0..15
		uint16_t selector; // a code segment selector in GDT or LDT
		uint8_t zero;      // unused, set to 0
		uint8_t type_attr; // type and attributes, see below
		uint16_t offset_2; // offset bits 16..31F
}__attribute__((__packed__));

/**
 * how the cpu knows about the IDT
 */
struct IdtDiscriptor {
		uint16_t size;
		uint32_t offset;
}__attribute__((packed));

/**
 * funct pointers to the ASM interrupt handler
 */
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
//------------------------------------------
extern void* sysCallAsmHandler;

class InterruptDiscriptorTable {
	private:
		/**
		 * max interrupt number
		 */
		size_t size;
		/**
		 * the IDT
		 */
		IdtEntry _idt[255];
		/**
		 * the descriptor used by the cpu to deal with the IDT
		 */
		IdtDiscriptor idtd;
	public:
		/**
		 *
		 * @param really a funct pointer to the **ASM** interrupt handleer
		 * @param selector that the code should run in
		 * @return encoded entry for the IDT
		 */
		IdtEntry encode(uint32_t offset, uint16_t selector);
		/**
		 * create the IDT descriptor and load a pointer into the CPU
		 */
		void load( ) {
			//get the size of the IDT. -1 is x86 BULLSHIT
			size_t sizeOfidt = (48 * sizeof(IdtEntry)) - 1;
			//build descriptor. no i cant spell
			idtd.offset = (uint32_t) _idt;
			idtd.size = sizeOfidt;
			//send the mem address to asm. tell cpu where IDT is
			asm ("LIDT %[idtd]" : : [idtd] "m" (idtd));
		}
		InterruptDiscriptorTable( );
		void build();
};

#endif /* INTERRUPTDISCRIPTORTABLE_H_ */
