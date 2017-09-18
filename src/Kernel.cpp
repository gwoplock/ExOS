/*
 * kernel.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */
#include "Kernel.h"

#include "drivers/ProgrammableInterruptController.h"
#include "memory/alloc/PageFrameAllocator.h"
#include "drivers/Keyboard.h"
#include "interrupts/InterruptDescriptorTable.h"
#include "drivers/TTY/Console.h"
//#include "memory/alloc/malloc.h"
#include "memory/structures/GlobalDescriptorTable.h"
#include "memory/structures/PageTable.h"
#include "drivers/PCI/PCI.h"
#include "drivers/PCI/PCIDeviceList.h"
#include "multiboot_spec/Multiboot.h"
#include "memory/Mem.h"
#include "utils/printf/Printf.h"
#include "drivers/CMOS/CMOS.h"
#include "drivers/floppy/Floppy.h"

InterruptDescriptorTable idt;
GlobalDescriptorTable gdt;
PageTable pageTable;
Keyboard KB;
PageFrameAllocator frameAlloc;

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
	void kernelMain(multiboot_info_t* mbd) {
		//turn off interrupts before configed
		asm("cli");
		//clear screen, set the pointer to the start of the VGA buffer.
		terminalInit((uint16_t*) 0xC00B8000);
		// Green on black!
		terminalSetColor(vgaEntryColor(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
        terminalWriteLine("Terminal active, Welcome to ExOS!");
        terminalWriteLine("Preparing your system:");
        terminalWriteString("  Preparing GDT...");
		//build and replce grub's GDT with a custom writable one.
		gdt.build( );
		gdt.load( );
        terminalWriteLine(" Done!");
        terminalWriteString("  Preparing the page table...");
		//rebuild page table. replaces the one built in boot.s
		pageTable.build( );
        terminalWriteLine(" Done!");
        terminalWriteString("  Setting up interrupts...");
		//sets up interrups and enables them
		interruptSetUp( );
        terminalWriteLine(" Done!");
        terminalWriteString("  Preparing the memory allocator...");
		//get the memory map from grub
		getMemMap(mbd);
		//build the page frame allocator (allocate physical memory)
		frameAlloc.build( );
		//set malloc's support vars
		mallocInit( );
        terminalWriteLine(" Done!");
        // Get the floppy drive types from CMOS
        terminalWriteString("  Finding floppy drive types...");
        fdtypes_t drives = getDriveTypes();
        terminalWriteLine(" Done!");
        printf ("  Master: %x\n", drives.master);
        printf ("  Slave: %x\n", drives.slave);
        // Keep track of which drives are supported (only 1.44M 3.5 inch)
        uint8_t masterSupported = drives.master == _1440KB35;
        uint8_t slaveSupported = drives.slave == _1440KB35;
        if (!(masterSupported || slaveSupported)) {
            printf ("  No supported drives found :(\n");
        } else {
            printf ("  Initializing floppy ISA DMA transfer...");
            initFloppyDMA ();
            printf (" Done!\n");
        }
        terminalWriteString("  Finding PCI buses...");
		//find the valid PCI buses
		PCIInit();
        terminalWriteLine(" Done!");
        terminalWriteString("  Finding USB host controllers...");
		//find the (3 or less) USB host controllers. all have the same class/subclass code.
		PCIDeviceList usbHostControllers(0x0C, 0x03, false);
        terminalWriteLine(" Done!");
        terminalWriteLine("!!!!ExOS fully booted!!!!");
        printf("Test printf %d %c\n", 42, 'B');
        printf("Newline is 0x%x%c", '\n', '\n');
        for (int cx = 0; cx < 10; cx++) {
            printf("%d", cx);
        }
		//dont return.
		while (true) {
			asm("hlt");
		}
	}

#if defined(__cplusplus)
}
#endif

void interruptSetUp( ) {
	//build the IDT.
	idt.build( );
	//set the interrupt lines for the PIC
	PICRemap(0x20, 0x28);
	//mask the timer line
	IRQSetMask(0);
	//load it to the CPU
	idt.load( );
	//enable interupts
	asm("sti");
}

