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
		  printf("top = %x", top);
		  BREAKPOINT
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
	BREAKPOINT
	printf("in Malloc, top  = %x\n", top);
	memHeader* c = (memHeader*)&kernelEnd;
	
	for (; c != nullptr; c = c->next) {
		printf("looped\n");
		printf("set c to %x\n", c);
		if (c->next == nullptr) {
			printf("set c to %x\n", c);
			printf("next is nullptr\n");
			printf("top addr = %x\n (uint32_t)top = %x", (uint32_t)c + sizeof(memHeader) + size + sizeof(memHeader), (uint32_t)top);
			if ( ((uint32_t)top >= (uint32_t)c + sizeof(memHeader) + size + sizeof(memHeader)) && !c->used) {
				printf("have space\n");
				//TODO this may not work
				printf("set c to %x\n", c);
				memHeader* temp = (memHeader*)((uint32_t)c + sizeof(c) + size);
				printf("set temp to, %x\n", temp);
				temp->next = nullptr;
				printf("set temps next\n");
				temp->used = false;
				printf("set temp as unsed\n");
				c->next = temp;
				printf("set c-> next to temp\n");
				c->used = true;
				printf("set c as used \n");
				return c+1;
			} else {
				printf("dont have space\n");
				void* startOfNewMem = frameAlloc.allocatePhysMem(size,pageTable.getKernelStart());
				size_t sizeOfNewMem = ((size)/FOUR_KB + ( (size & 0xFFF) != 0)) * FOUR_KB;
				top = (void*) ((size_t) top + sizeOfNewMem + ((size_t)startOfNewMem - (size_t)top) );
				return malloc(size);
			}
		} else if (!c->used && (unsigned)(c->next - c) == size) {
			printf("next is just enough space\n");
			c->used = true;
			return c+1;
		} else if (!c->used && (unsigned)(c->next - c) >= (size + sizeof(memHeader))) {
			printf("next is too big\n");
			memHeader* temp = (memHeader*)(((uint8_t*)(c+1)) + size);
			temp->next = c->next;
			temp->used = false;
			c->next = temp;
			c->used = true;
			return c+1;
		} else {
			printf("continuing \n");
			continue;
		}
	}
	printf("returning nullptr\n");
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