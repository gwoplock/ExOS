/*
 * kernel.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */
#include "kernel.h"



#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
void kernelMain(void/*multiboot shit*/){
	asm("cli");
	gdt.load();
	interruptSetUp();

}

#if defined(__cplusplus)
}
#endif

void interruptSetUp(){
	picRemap(0x20, 0x28);
	idt.load();
	maskIrq(0);
}

void fixPaging(){
	pageTable = PageTable(true);
}
