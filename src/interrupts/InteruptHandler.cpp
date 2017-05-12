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
	writeInt((uint32_t)line);
	terminalPutChar(' ');
	//if(line ==1/*KB*/){
	//	uint8_t key = KB.getKey();
	//	if (key != '\0') {
	//		//nope. put that key down
	//		terminalPutChar(key);
	//	} else {
	//		//handle the specail key
	//		//terminalHandleSpecialKey(_newKeyScancode, &mods);
	//	}
	//}
	sendEOI(line);
}

void isr_handler(int interruptNumber){
	writeInt((uint32_t)interruptNumber);
	terminalPutChar(' ');
}

#if defined(__cplusplus)
}
#endif
