/*
 * InteruptHandler.c
 *
 *  Created on: Feb 27, 2017
 *      Author: garrett
 */

#include "InterruptHandler.h"

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif

void irq_handler(int line){
	if(line ==1/*KB*/){
		uint8_t scanCode = KB.getScancode();
		uint8_t key = KB.getKey(scanCode);
		if(key != '\0' && !(scanCode & 0x80)){
			terminalPutChar(key);
		} else {
			terminalHandleSpecialKey(scanCode, KB.getModkeys());
		}
	}
	PIC_sendEOI(line);
}

void isr_handler(int interruptNumber){
	terminalPutChar(' ');
	writeInt((uint32_t)interruptNumber);

}

#if defined(__cplusplus)
}
#endif
