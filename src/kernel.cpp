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

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
	void kernelMain(void/*multiboot shit*/) {
		asm("cli");
		/* begin test code*/
		//gdt test -> broken
		gdt.load( );
		//term test
		terminalInit((uint16_t*) 0xC00B8000);
		terminalWriteString("Hello World!");
		//paging test
		pageTable.build( );
		//IDT test
		interruptSetUp();
		//KB test
		uint8_t keyOld = '\0';
		while (true) {
			uint8_t keyNew = KB.getKey( );
			if (keyNew != keyOld && keyNew != '\0') {
				terminalPutChar(keyNew);
				keyOld = keyNew;
			}
		}

		/*end test code*/
		while (true) {
			asm("hlt");
		}

	}

#if defined(__cplusplus)
}
#endif

void interruptSetUp( ) {
	//picRemap(0x20, 0x28);
	idt.load( );
	//maskIrq(0);
	asm("sti");
}

void fixPaging( ) {
	//pageTable = PageTable(true);
}
