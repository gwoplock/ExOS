/*
 * maloc.c
 *
 *  Created on: Jul 3, 2017
 *      Author: garrett
 */

#include "malloc.h"
#include "../../kernel.h"
#include "../structures/PageTable.h"
#include "PageFrameAllocator.h"

/**
 * top of the paged in mem
 */
void* top;
/**
 * base of free mem
 */
void* base;

/**
 * set up the vars needed for malloc
 */
void mallocInit( ) {
	base = &kernelEnd;
	top = (void*) ( (size_t)( &kernelSize) + (uint32_t)
			& kernelStart + fourKb);
}
#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
/**
 *  mem alloc
 * @param size to alloc
 */
void* malloc(size_t size) {
	size_t space = (size_t) top - (size_t) base;
	if (space > size) {
		//if there is space in the current phys mem allocated
		void* oldBase = base;
		//move the base address
		base = (void*) ((size_t) base + size);
		//return the start of allocated space
		return oldBase;
	} else {
		//TODO take into account out of mem
		void* startOfNewMem = frameAlloc.allocatePhysMem(size - space,pageTable.getKernelStart());
		size_t sizeOfNewMem = ((size-space)/fourKb + ( ((size-space) & 0xFFF) != 0)) * fourKb;
		top = (void*) ((size_t) top + sizeOfNewMem + ((size_t)startOfNewMem - (size_t)top) );
		return malloc(size);
	}
}
/**
 * free mem
 * @param ptr to the mem to free
 */
void free(void *ptr){
//TODO
}
#if defined(__cplusplus)
}/* Use C linkage for kernel_main. */
#endif
