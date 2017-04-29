/*
 * mem.h
 *
 *  Created on: Apr 29, 2017
 *      Author: garrett
 */

#include "mem.h"

MultibootMemoryMap memMap[256];
void getMemMap(multiboot_info_t* mbt) {
	uint32_t vKernelStart = (uint32_t) pageTable.getKernelStart();
	mbt = (multiboot_info_t*) ((int32_t) mbt + vKernelStart);
	MultibootMemoryMap* mmap = (MultibootMemoryMap*) (mbt->mmap_addr
			+ vKernelStart);
	int i = 0;
	while ((uint32_t) mmap < mbt->mmap_addr + mbt->mmap_length + vKernelStart) {
		memMap[i] = *mmap;
		mmap = (MultibootMemoryMap*) ((unsigned int) mmap + mmap->size
				+ sizeof (mmap->size));
		i++;
	}
	memMap[i].type = 0xDEADC0DE;
}
