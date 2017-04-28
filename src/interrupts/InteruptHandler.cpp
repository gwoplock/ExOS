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

void irq_handler(int irq){

}

void isr_handler(int line){
	//handle IRQ

	sendEOI(line);
}

#if defined(__cplusplus)
}
#endif
