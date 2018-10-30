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
#include "memory/Mem.h"
#include "utils/printf/Printf.h"

void *top;


/**
 * set up the vars needed for malloc
 */
void mallocInit()
{
	top = (void*)((((size_t)(&kernelSize) + (uint32_t) & kernelStart) / FOUR_KB + 1) * FOUR_KB /*+
	      FOUR_KB*/ - 1);
	((memHeader*)&kernelEnd)->used = false;
	((memHeader*)&kernelEnd)->next = nullptr;

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
	memHeader* c = (memHeader*)&kernelEnd;
	for (; c != nullptr; c = c->next) {
		if (c->next == nullptr) {
			if ( ((uint32_t)top >= (uint32_t)c + sizeof(memHeader) + size + sizeof(memHeader)) && !c->used) {
				//TODO this may not work
				memHeader* temp = (memHeader*)((uint32_t)c + sizeof(c) + size);
				temp->next = nullptr;
				temp->used = false;
				c->next = temp;
				c->used = true;
				return c+1;
			} else {
				void* startOfNewMem = frameAlloc.allocatePhysMem(size,pageTable.getKernelStart());
				size_t sizeOfNewMem = ((size)/FOUR_KB + ( (size & 0xFFF) != 0)) * FOUR_KB;
				top = (void*) ((size_t) top + sizeOfNewMem + ((size_t)startOfNewMem - (size_t)top) );
				return malloc(size);
			}
		} else if (!c->used && (unsigned)(c->next - c) == size) {
			c->used = true;
			return c+1;
		} else if (!c->used && (unsigned)(c->next - c) >= (size + sizeof(memHeader))) {
			memHeader* temp = (memHeader*)(((uint8_t*)(c+1)) + size);
			temp->next = c->next;
			temp->used = false;
			c->next = temp;
			c->used = true;
			return c+1;
		} else {
			continue;
		}
	}
return nullptr;

}

/**
 * free mem
 * @param ptr to the mem to free
 */
void free(void *ptr)
{
	memHeader *i = (memHeader*)&kernelEnd;
	for (; i < top && i->next <= ptr && i->next->next > ptr; i = i->next);
	//TODO hmm something is fishy about this
	if (i == top) {
		((memHeader*)ptr)->next = i->next;
	}
	((memHeader*)ptr)->used = false;
	i->next = (memHeader*)ptr;
	compFreeSpace();
}

#if defined(__cplusplus)
}/* Use C linkage for kernel_main. */
#endif

void compFreeSpace()
{
	for (memHeader *i = (memHeader*)&kernelEnd; i < top; i = i->next) {
		if (i->used == false && i->next->used == false) {
			i->next = i->next->next;
		}
	}
}

void *realloc(void *ptr, size_t size)
{
	memHeader *i = (memHeader*)&kernelEnd;
	for (; i < top && i->next <= ptr && i->next->next > ptr; i = i->next);
	memHeader *next = i->next;
	if ((uint8_t*) ptr + size == (uint8_t*)next) {
		return ptr;
	} else if ((uint8_t*) ptr + size < (uint8_t*)next) {
		free((uint8_t *) ptr + size);
		return ptr;
	} else if ((uint8_t*) ptr + size < (uint8_t*)next) {
		if (!next->used) {
			size_t found = 0;
			while (!next->used && next->next != nullptr && found <= size - (uint32_t)i - (uint32_t)next){
				found += next - next->next;
				next = next->next;
			}
			if(found == size){
				i->next = next;
				return ptr;
			}
		}
		void* res = malloc(size);
		memcpy(res, ptr, i-next);
		free(ptr);
		return res;
	}
return nullptr;
}