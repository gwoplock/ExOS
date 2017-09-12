/*
 * abort.c

 *
 *  Created on: Aug 14, 2017
 *      Author: garrett
 */
#include "clib_misc/abort.h"
#include "drivers/TTY/Console.h"

extern "C"
void /*__cxxabiv1::*/__cxa_pure_virtual(void) {
	terminalWriteString("pure virtual method called.......");
	abort( );
}

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
	/**
	 * std abort function. does nothing right now.
	 */
	void abort(void) {
		terminalWriteString("ERROR....... KERNEL PANIC......... PLEASE REBOOT");
		asm("cli");
		asm("hlt");
	}
#if defined(__cplusplus)
}/* Use C linkage for kernel_main. */
#endif

