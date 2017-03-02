/*
 * kernel.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */
#include "kernel.h"

GlobalDescriptorTable gdt = GlobalDescriptorTable();
InterruptDiscriptorTable idt = InterruptDiscriptorTable();


#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
void kernelMain(void/*multiboot shit*/){
	asm("cli");
	gdt.load();
	picRemap(0x20, 0x28);
	idt.load();
	maskIrq(0);
}

#if defined(__cplusplus)
}
#endif
