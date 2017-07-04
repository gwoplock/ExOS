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

typedef int32_t int;
typedef int64_t long;

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
	void kernelMain(multiboot_info_t* mbd) {
		asm("cli");
		terminalInit((uint16_t*) 0xC00B8000);
        // Green on black!
        terminalSetColor (vgaEntryColor (VGA_COLOR_GREEN, VGA_COLOR_BLACK));
		gdt.build( );
		gdt.load( );
		pageTable.build( );
		interruptSetUp( );
		getMemMap(mbd);
		frameAlloc.build();
		mallocInit();

        /* Tests for malloc go here */
        int count = 2
        long *array = malloc (count * sizeof (long));
        // Populate array
        for (int cx = 0; cx < count; cx++) {
            *(array + cx) = cx;
        }
        // Print array
        for (int cx = 0; cx < count; cx++) {
            // writeInt should really be a writeLong shoudln't it...
            writeInt (*(array + cx));
        }
        /* End malloc tests */

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
