/*
 * maloc.c
 *
 *  Created on: Jul 3, 2017
 *      Author: garrett
 */

#include "memory/alloc/Malloc.h"
#include "Kernel.h"
#include "memory/structures/PageTable.h"
#include "memory/alloc/PageFrameAllocator.h"

void *top;
void*;

/**
 * set up the vars needed for malloc
 */
void mallocInit()
{
	top = (((size_t)(&kernelSize) + (uint32_t) & kernelStart - vKernelStart) / FOUR_KB + 1) * FOUR_KB +
	      FOUR_KB - 1;
	&kernelEnd->used = false;
	&kernelEnd->next = nullptr;

	/*
	base = &kernelEnd;
	top = (void*) ( (size_t)( &kernelSize) + (uint32_t)
			& kernelStart + FOUR_KB);
	*/
}

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif

/**
 *  mem alloc
 * @param size to alloc
 */
void *malloc(size_t size)
{
	size += sizeof(memHeader);
	//size_t space = (size_t) top - (size_t) & kernelEnd;
	//if (space > size) {
	//have space
	for (memHeader *i; i < &kernelEnd; i = i->next) {
		if (next == nullptr && (i - top) > size && !(i->used)) {
			//at end
			current->used = true;
			if (current->next == ((memHeader * )(((uint8_t *) i +1) + size))) {
				((memHeader * )(((uint8_t *) i+1) + size))->used = false;
				((memHeader * )(((uint8_t *) i+1) + size))->next = i->next;
			}
			i->used = true;
			i->next = ((uint8_t *) i+1) + size;
			return i + sizeof(memHeader);
		} else if ((i - i->next) > size && !(i->used)) {
			return i + sizeof(memHeader);
		}
	}
	//} else {
	//need to page in
	//TODO handle out of mem
	void *startOfNewMem = frameAlloc.allocatePhysMem(size - space, pageTable.getKernelStart());
	size_t sizeOfNewMem = ((size - space) / FOUR_KB + (((size - space) & 0xFFF) != 0)) * FOUR_KB;
	top = (void *) ((size_t) top + sizeOfNewMem + ((size_t) startOfNewMem - (size_t) top));
	return malloc(size);
	//}

	/*
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
		size_t sizeOfNewMem = ((size-space)/FOUR_KB + ( ((size-space) & 0xFFF) != 0)) * FOUR_KB;
		top = (void*) ((size_t) top + sizeOfNewMem + ((size_t)startOfNewMem - (size_t)top) );
		return malloc(size);
	}
	*/
}

/**
 * free mem
 * @param ptr to the mem to free
 */
void free(void *ptr)
{
//TODO
}

#if defined(__cplusplus)
}/* Use C linkage for kernel_main. */
#endif
