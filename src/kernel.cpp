/*
 * kernel.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */
#include "kernel.h"

InterruptDiscriptorTable idt = InterruptDiscriptorTable();
GlobalDescriptorTable gdt = GlobalDescriptorTable();
PageTable pageTable = PageTable();
Keyboard KB = Keyboard();

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
void kernelMain(void/*multiboot shit*/){
	asm("cli");
	/* begin test code*/
	gdt.load();
	terminalInit((uint16_t*)0xC00B8000);
	terminalWriteString("Hello World!");
	interruptSetUp();
	/*end test code*/

}

#if defined(__cplusplus)
}
#endif

void interruptSetUp(){
	picRemap(0x20, 0x28);
	idt.load();
	maskIrq(0);
	//asm("sti");
}

void fixPaging(){
	//pageTable = PageTable(true);
}
