/*
 * kernel.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */
#include "kernel.h"

#include "drivers/ProgrammableInterruptController.h"
#include "memory/alloc/PageFrameAllocator.h"
#include "drivers/Keyboard.h"
#include "interrupts/InterruptDiscriptorTable.h"
#include "drivers/Console.h"
//#include "memory/alloc/malloc.h"
#include "memory/structures/GlobalDescriptorTable.h"
#include "memory/structures/PageTable.h"
#include "drivers/PCI/PCI.h"
#include "drivers/PCI/PCIDeviceList.h"
#include "multiboot_spec/multiboot.h"
#include "memory/mem.h"
#include "Utils/printf/printf.h"

InterruptDiscriptorTable idt;
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
        terminalWriteString("  Finding PCI buses...");
		//find the valid PCI buses
		PCIInit();
        terminalWriteLine(" Done!");
        terminalWriteString("  Finding USB host controllers...");
		//find the (3 or less) USB host controllers. all have the same class/subclass code.
		PCIDeviceList usbHostControllers(0x0C, 0x03, false);
        terminalWriteLine(" Done!");
        terminalWriteLine("\n\n\n\n!!!!ExOS fully booted!!!!");
        printf("Test printf %d %c", 42, 'B');
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
	PIC_remap(0x20, 0x28);
	//mask the timer line
	IRQ_set_mask(0);
	//load it to the CPU
	idt.load( );
	//enable interupts
	asm("sti");
}

