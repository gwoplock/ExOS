/*
 * maloc.c
 *
 *  Created on: Jul 3, 2017
 *      Author: garrett
 */

#include "malloc.h"

void* top;
void* base;

void mallocInit( ) {
	base = &kernelEnd;
	top = (void*) ( (size_t)( &kernelSize) + (uint32_t)
			& kernelStart + fourKb);
}

void* malloc(size_t size) {
	BREAKPOINT
	writeInt(size);
	size_t space = (size_t) top - (size_t) base;
	if (space > size) {
		void* oldBase = base;
		base = (void*) ((size_t) base + size);
		return oldBase;
	} else {
		//TODO take into account out of mem
		//writeInt((uint32_t)top);
		//terminalPutChar(' ');
		void* startOfNewMem = frameAlloc.allocatePhysMem(size - space,pageTable.getKernelStart());
		size_t sizeOfNewMem = ((size-space)/fourKb + ( ((size-space) & 0xFFF) != 0)) * fourKb;
		top = (void*) ((size_t) top + sizeOfNewMem + ((size_t)startOfNewMem - (size_t)top) );
		return malloc(size);
	}
}
