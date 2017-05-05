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

void memcpy(void* to, void* from, size_t length) {
	int* toArr = (int*) to;
	int* fromArr = (int*) from;
	for (size_t i = 0; i < length / sizeof(int); i++) {
		toArr[i] = fromArr[i];
	}
	for (size_t i = 0; i < length % sizeof(int); i++) {
		* ((char*) to + i + length - length % sizeof(int)) = * ((char*) from + i
				+ length - length % sizeof(int));
	}
}
