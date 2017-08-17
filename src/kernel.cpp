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
		BREAKPOINT
		asm("cli");
		terminalInit((uint16_t*) 0xC00B8000);
		// Green on black!
		terminalSetColor(vgaEntryColor(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
		terminalWriteString(
				"Terminal active, Welcome to ExOS. Now preparing your system. preparing GDT...");
		gdt.build( );
		gdt.load( );
		terminalWriteString(" Done. preparing the page Table...");
		pageTable.build( );
		terminalWriteString(" Done. setting up interrupts...");
		interruptSetUp( );
		terminalWriteString(" Done. Preparing the memory allocator...");
		getMemMap(mbd);
		frameAlloc.build( );
		mallocInit( );
		terminalWriteString(" Done. Finding PCI buses...");
		PCIInit();
		terminalWriteString(" Done. Finding USB host controllers...");
		//PCIDeviceList usbHostControllers(0x0C, 0x03, false);
		terminalWriteString("Done.");
		terminalWriteString("   !!!!your computer is booted!!!");
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
