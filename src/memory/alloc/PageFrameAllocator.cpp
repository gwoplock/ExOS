/*
 * PageFrameAllocator.cpp
 *
 *  Created on: Apr 29, 2017
 *      Author: garrett
 */
#include "PageFrameAllocator.h"
#include "../Mem.h"
#include "../structures/PageTable.h"

PageFrameAllocator::PageFrameAllocator( ) {
	// TODO Auto-generated constructor stub

}
/**
 * set up the allocator.
 */
void PageFrameAllocator::build( ) {
	lastUsedPage = 0;
	//make all avalible
	for (int i = 0; i < (1024 * 1025) / 8; i++) {
		physPageAvalibility[i] = 0;
	}
	int i = 0;
	//read the parsed grub mem map, dead code = end of array
	while (i < 255 && memMap[i].type != 0xDEADC0DE) {
		if (memMap[i].type != 1) {
			//convert unavalible mem address
			uint32_t startPage = (uint64_t) memMap[i].base_addr / fourKb;
			uint32_t sizeInPages = (memMap[i].length / fourKb) + 1
					+ ( ((uint64_t) memMap[i].base_addr & 0xFFF) != 0);
			int byte = startPage / 8;
			int bit = startPage % 8;
			//for the unavlible mem, mark as such
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
	//same for the kernel
	size_t kernelPages =
			( ((size_t) ( &kernelSize) + (uint32_t)
					& kernelStart - (uint32_t) pageTable.getKernelStart( ))
					/ fourKb + 1);
	int byte = KERNEL_PAGE_START / 8;
	int bit = KERNEL_PAGE_START % 8;
	for (size_t k = 0; k < kernelPages; k++) {
		physPageAvalibility[byte] |= 0b1 << bit;
		bit++;
		if (bit == 8) {
			bit = 0;
			byte++;
		}
	}
}
/**
 * check if phys mem is available
 * @param page to check
 * @return the availability
 */
bool PageFrameAllocator::isAvalible(int page) {
	size_t byte = page / 8;
	size_t bit = page % 8;
	return (bool) ! (physPageAvalibility[byte] & (0b1 << bit));
}

/**
 * allocate phys mem to a process
 * @param size to allocate
 * @param base Virt Address to start checking, useful for the OS
 */
void* PageFrameAllocator::allocatePhysMem(size_t size, void* baseVirtAddress) {
	//covert bytes to pages
	uint32_t sizeInPages = (size / fourKb) + ( (size & 0xFFF) != 0);
	//find the vert address we'll use
	void* vertAddress = getNextVirtAddr(sizeInPages, baseVirtAddress);
	//out of mem
	if (vertAddress == (void*) -1) {
		return (void*) -1;
	}
	void* toRet = (void*) -1;
	//page in the phys mem
	while (sizeInPages) {
		//if its availible page it
		if (isAvalible(lastUsedPage)) {
			//if we havent set the start address we return set it
			if (toRet == (void*) -1) {

				toRet = pageTable.page((void*) (lastUsedPage * fourKb),
						vertAddress, fourKb);
			} else {
				//page in the rest
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
	//starting at the base addr, find the next section of mem that is big enough
	for (int i = ((size_t) baseVirtAddress / fourKb); i < 1024 * 1024; i++) {
		//check if its already paged in
		if ( !pageTable.getPageTables( )[i].present) {
			uint32_t n = 0;
			//check the next pages till we have all the pages we need
			for (; n < sizeInPages; n++) {
				if (pageTable.getPageTables( )[i + n].present) {
					i += n;
					break;
				}
				if (n == sizeInPages - 1) {
					return (void*) (i * fourKb);
				}
			}
			//this was added during debug, i dont think its ever used but im going to leave it here.
			if (n == 0) {
				return (void*) (i * fourKb);
			}
		}
	}
	return (void*) -1;
}
