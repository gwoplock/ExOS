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

void * operator new(size_t size)
{

    void * p = malloc(size);
    return p;
}

void operator delete(void * p)
{

}
void operator delete(void*, long unsigned int){

}

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
	void kernelMain(multiboot_info_t* mbd) {
		asm("cli");
		terminalInit((uint16_t*) 0xC00B8000);
        // Green on black!
        terminalSetColor (vgaEntryColor (VGA_COLOR_GREEN, VGA_COLOR_BLACK));
        terminalWriteString("Terminal active, Welcome to ExOS. Now preparing your system. preparing GDT...");
		gdt.build( );
		gdt.load( );
		terminalWriteString(" Done. preparing the page Table...");
		pageTable.build( );
		terminalWriteString(" Done. setting up interrupts...");
		interruptSetUp( );
		terminalWriteString(" Done. Preparing the memory allocator...");
		getMemMap(mbd);
		frameAlloc.build();
		mallocInit();
        terminalWriteString(" Done. ");
        //TESTING placement new.
terminalWriteString("!!!foobar.!!!!");
void* test = malloc(10);
        //END TESTING
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
