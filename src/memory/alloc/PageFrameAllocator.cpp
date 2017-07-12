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
void PageFrameAllocator::build( ) {
	lastUsedPage = 0;
	for (int i = 0; i < (1024 * 1025) / 8; i++) {
		physPageAvalibility[i] = 0;
	}
	int i = 0;
	while (i < 255 && memMap[i].type != 0xDEADC0DE) {
		if (memMap[i].type != 1) {
			uint32_t startPage = (uint64_t) memMap[i].base_addr / fourKb;
			uint32_t sizeInPages = (memMap[i].length / fourKb) + 1
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
			( ((size_t) ( &kernelSize) + (uint32_t)
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

bool PageFrameAllocator::isAvalible(int page) {
	size_t byte = page / 8;
	size_t bit = page % 8;
	return (bool) ! (physPageAvalibility[byte] & (0b1 << bit));
}

void* PageFrameAllocator::allocatePhysMem(size_t size, void* baseVirtAddress) {
	uint32_t sizeInPages = (size / fourKb) + ( (size & 0xFFF) != 0);
	void* vertAddress = getNextVirtAddr(sizeInPages, baseVirtAddress);

	if (vertAddress == (void*) -1) {
		return (void*) -1;
	}

	void* toRet = (void*) -1;
	while (sizeInPages) {

		if (isAvalible(lastUsedPage)) {

			if (toRet == (void*) -1) {

				toRet = pageTable.page((void*) (lastUsedPage * fourKb),
						vertAddress, fourKb);
			} else {
				pageTable.page((void*) (lastUsedPage * fourKb), vertAddress,
				fourKb);
			}
			sizeInPages--;
			vertAddress = (void*) ((uint32_t) vertAddress + fourKb);
			lastUsedPage++;
		}
	}
	return toRet;
}

void* PageFrameAllocator::getNextVirtAddr(uint32_t sizeInPages,
		void* baseVirtAddress) {
	for (int i = ((size_t) baseVirtAddress / fourKb); i < 1024 * 1024; i++) {
		if ( !pageTable.getPageTables( )[i].present) {
			uint32_t n = 0;
			for (; n < sizeInPages; n++) {
				if (pageTable.getPageTables( )[i + n].present) {
					i += n;
					break;
				}
				if (n == sizeInPages - 1) {
					return (void*) (i * fourKb);
				}
			}
			if (n == 0) {
				return (void*) (i * fourKb);
			}
		}
	}
	return (void*) -1;
}
