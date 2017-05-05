/*
 * kernel.h
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */
#ifndef KERNEL_H_
#define KERNEL_H_

#include "memory/GlobalDescriptorTable.h"
#include "global.h"
#include "interrupts/InterruptDiscriptorTable.h"
#include "drivers/ProgrammableInterruptController.h"
#include "memory/PageTable.h"

extern GlobalDescriptorTable gdt;
extern InterruptDiscriptorTable idt;
extern PageTable pageTable;

void interruptSetUp();
void fixPaging();

#endif
