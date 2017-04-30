/*
 * PageFrameAllocator.cpp
 *
 *  Created on: Apr 29, 2017
 *      Author: garrett
 */
#include "PageFrameAllocator.h"

PageFrameAllocator::PageFrameAllocator( ) {
	// TODO Auto-generated constructor stub

}
PageFrameAllocator::PageFrameAllocator(bool buildFlag) {
	buildFlag = !buildFlag;
	lastUsedPage = 0;
	for (int i = 0; i < (1024 * 1025) / 8; i++) {
		physPageAvalibility[i] = 0;
	}
	int i = 0;
	while (i < 255 && memMap[i].type != 0xDEADC0DE) {
		if (memMap[i].type != 1) {
			uint32_t startPage = (uint64_t) memMap[i].base_addr / fourKb;
			uint64_t sizeInPages = (memMap[i].length / fourKb) + 1
					+ ( ((uint64_t) memMap[i].base_addr & 0xFFF) != 0);
			int byte = startPage / 8;
			int bit = startPage % 8;
			for (uint32_t k = 0; k < sizeInPages; k++) {
				physPageAvalibility[byte] |= 0b1 << bit;
				bit++;
				if (bit == 8) {
					bit = 0;
					byte++;
				}
			}
		}
		i++;
	}
	size_t kernelPages =
			( ( (size_t)( &kernelSize) + (uint32_t)
					& kernelStart - (uint32_t) pageTable.getKernelStart( ))
					/ fourKb + 1);
	int byte = KernelPageStart / 8;
	int bit = KernelPageStart % 8;
	for (size_t k = 0; k < kernelPages; k++) {
		physPageAvalibility[byte] |= 0b1 << bit;
		bit++;
		if (bit == 8) {
			bit = 0;
			byte++;
		}
	}
}
