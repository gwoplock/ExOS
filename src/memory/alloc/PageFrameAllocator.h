/*
 * PageFrameAllocator.h
 *
 *  Created on: Apr 29, 2017
 *      Author: garrett
 */

#ifndef PAGEFRAMEALLOCATOR_H_
#define PAGEFRAMEALLOCATOR_H_

#include "../../Global.h"

//#include "../../kernel.h"
//#include "../structures/PageTable.h"

class PageFrameAllocator {
	private:
		/**
		 * last page checked
		 */
		uint32_t lastUsedPage;
		/**
		 * bit array for every page
		 */
		uint8_t physPageAvalibility[ (1024 * 1024) / 8];
	public:
		PageFrameAllocator( );
		/**
		 * set up the allocator.
		 */
		void build( );
		/**
		 * check if phys mem is available
		 * @param page to check
		 * @return the availability
		 */
		bool isAvalible(int page);
		/**
		 * allocate phys mem to a process
		 * @param size to allocate
		 * @param base Virt Address to start checking, useful for the OS
		 */
		void* allocatePhysMem(size_t sizeToAlloc, void* baseVirtAddress);
		/**
		 * get next open pages
		 * @param size In Pages
		 * @param  base Virt Address to start checking, useful for the OS
		 */
		void* getNextVirtAddr(uint32_t sizeInPages, void* baseVirtAddress);

};

#endif /* PAGEFRAMEALLOCATOR_H_ */
