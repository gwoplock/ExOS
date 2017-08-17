/*
 * InteruptHandler.c
 *
 *  Created on: Feb 27, 2017
 *      Author: garrett
 */

#include "InterruptHandler.h"
#include "../kernel.h"
#include "../drivers/Keyboard.h"
#include "../drivers/Console.h"
#include "../drivers/ProgrammableInterruptController.h"
#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif

	void irq_handler(int line) {
		if (line == 1/*KB*/) {
			uint8_t scanCode = KB.getScancode( );
			uint8_t key = KB.getKey(scanCode);
			if (key != '\0' && ! (scanCode & 0x80)) {
				terminalPutChar(key);
			} else {
				terminalHandleSpecialKey(scanCode, KB.getModkeys( ));
			}
		}
		PIC_sendEOI(line);
	}

	void isr_handler(int interruptNumber) {
		terminalPutChar(' ');
		writeInt((uint32_t) interruptNumber);

	}

#undef return

#if defined(__cplusplus)
}
#endif
