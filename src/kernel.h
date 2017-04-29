/*
 * kernel.h
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */


#include "memory/GlobalDescriptorTable.h"
#include "global.h"
#include "interrupts/InterruptDiscriptorTable.h"
#include "drivers/ProgrammableInterruptController.h"
#include "memory/PageTable.h"


void interruptSetUp();
void fixPaging();
