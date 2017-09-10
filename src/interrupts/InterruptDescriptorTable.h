/*
 * InterruptDescriptorTable.h
 *
 *  Created on: Feb 27, 2017
 *      Author: garrett
 */

#ifndef INTERRUPTDESCRIPTORTABLE_H_
#define INTERRUPTDESCRIPTORTABLE_H_

#include "../Global.h"

/**
 * structure used by the cpu to handler interrupts
 */
struct IdtEntry {
		uint16_t offset1; // offset bits 0..15
		uint16_t selector; // a code segment selector in GDT or LDT
		uint8_t zero;      // unused, set to 0
		uint8_t typeAttr; // type and attributes, see below
		uint16_t offset2; // offset bits 16..31F
}__attribute__((__packed__));

/**
 * how the cpu knows about the IDT
 */
struct IdtDescriptor {
		uint16_t size;
		uint32_t offset;
}__attribute__((packed));

/**
 * funct pointers to the ASM interrupt handler
 */
//possible should be void ____()
extern void* ISR0;
extern void* ISR1;
extern void* ISR2;
extern void* ISR3;
extern void* ISR4;
extern void* ISR5;
extern void* ISR6;
extern void* ISR7;
extern void* ISR8;
extern void* ISR9;
extern void* ISR10;
extern void* ISR11;
extern void* ISR12;
extern void* ISR13;
extern void* ISR14;
extern void* ISR15;
extern void* ISR16;
extern void* ISR17;
extern void* ISR18;
//--------------------------------------------
extern void* IRQ0;
extern void* IRQ1;
extern void* IRQ2;
extern void* IRQ3;
extern void* IRQ4;
extern void* IRQ5;
extern void* IRQ6;
extern void* IRQ7;
extern void* IRQ8;
extern void* IRQ9;
extern void* IRQ10;
extern void* IRQ11;
extern void* IRQ12;
extern void* IRQ13;
extern void* IRQ14;
extern void* IRQ15;
//------------------------------------------
extern void* sysCallAsmHandler;

class InterruptDescriptorTable {
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
		IdtDescriptor idtd;
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
		InterruptDescriptorTable( );
		void build();
};

#endif /* INTERRUPTDESCRIPTORTABLE_H_ */
