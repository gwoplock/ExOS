/*
 * kernel.h
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */
#ifndef KERNEL_H_
#define KERNEL_H_

#include "global.h"
#include "drivers/ProgrammableInterruptController.h"
#include "memory/alloc/PageFrameAllocator.h"
#include "drivers/Keyboard.h"
#include "interrupts/InterruptDiscriptorTable.h"
#include "drivers/Console.h"
#include "memory/alloc/malloc.h"
#include "memory/structures/GlobalDescriptorTable.h"
#include "memory/structures/PageTable.h"
#include "drivers/PCI/PCI.h"
#include "drivers/PCI/PCIDeviceList.h"

class InterruptDiscriptorTable;
class GlobalDescriptorTable;
class PageFrameAllocator;
class Keyboard;
class PageTable;

extern GlobalDescriptorTable gdt;
extern InterruptDiscriptorTable idt;
extern PageTable pageTable;
extern Keyboard KB;
extern PageFrameAllocator frameAlloc;

void interruptSetUp();
void fixPaging();

#endif
