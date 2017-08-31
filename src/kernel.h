/*
 * kernel.h
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */
#ifndef KERNEL_H_
#define KERNEL_H_

#include "global.h"


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

#endif
