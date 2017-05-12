/*
 * kernel.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */
#include "kernel.h"

InterruptDiscriptorTable idt;
GlobalDescriptorTable gdt;
PageTable pageTable;
Keyboard KB;
PageFrameAllocator frameAlloc;

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
	void kernelMain(multiboot_info_t* mbd) {
		asm("cli");
		terminalInit((uint16_t*) 0xC00B8000);
		gdt.build( );
		gdt.load( );
		pageTable.build( );
		interruptSetUp( );
		getMemMap(mbd);
		frameAlloc.build();
		while (true) {
			asm("hlt");
		}
	}

#if defined(__cplusplus)
}
#endif

void interruptSetUp( ) {
	idt.build( );
	PIC_remap(0x20, 0x28);
	IRQ_set_mask(0);
	idt.load( );
	asm("sti");
}

void fixPaging( ) {
	//pageTable = PageTable(true);
}
