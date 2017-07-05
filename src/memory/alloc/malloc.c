/*
 * maloc.c
 *
 *  Created on: Jul 3, 2017
 *      Author: garrett
 */

#include "malloc.h"

void* currentTop;
void* base;

void mallocInit( ) {
	base = &kernelEnd;
	currentTop = (void*) ( (size_t)( &kernelSize) + (uint32_t)
			& kernelStart + fourKb);
}

void* malloc(size_t size) {
	if ((size_t) currentTop - (size_t) base < size) {
		void* oldBase = base;
		base = (void*) ((size_t) base + size);
		return oldBase;
	} else {
		//TODO take into account out of mem
		currentTop = (void*) ((size_t)(frameAlloc.allocatePhysMem(
				size - ((size_t) currentTop - (size_t) base),
				(void*) pageTable.getKernelStart( )))
				+ ( ( (size / fourKb) + ( (size & 0xFFF) != 0)) * fourKb));
		return malloc(size);
	}
}
