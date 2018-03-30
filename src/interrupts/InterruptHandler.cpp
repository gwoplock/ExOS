/*
 * InteruptHandler.c
 *
 *  Created on: Feb 27, 2017
 *      Author: garrett
 */

#include "interrupts/InterruptHandler.h"
#include "Kernel.h"
#include "drivers/Keyboard.h"
#include "drivers/TTY/Console.h"
#include "drivers/ProgrammableInterruptController.h"
#include "utils/printf/Printf.h"

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
/**
 * handle hardware interrupts
 * @param line from the PIC
 */
	void IRQHandler(int line) {
		if (line == 1/*KB*/) {
			uint8_t scanCode = KB.getScancode( );
			uint8_t key = KB.getKey(scanCode);
			//if printable key
			if (key != '\0' && ! (scanCode & 0x80)) {
				//put the key
				terminalPutChar(key);
			} else {
				//handle the special key
				terminalHandleSpecialKey(scanCode, KB.getModkeys( ));
			}
		}
		PICSendEOI(line);
	}
/**
 * handle faults from the cpu
 * @param interrupt Number
 */
	void ISRHandler(int interruptNumber) {
		//print the interrupt number
		terminalPutChar(' ');
		writeInt((uint32_t) interruptNumber);
		BREAKPOINT
	}

#undef return

#if defined(__cplusplus)
}
#endif
