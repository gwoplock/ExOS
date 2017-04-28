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

PageTable pageTable;
void interruptSetUp();
void fixPaging();
