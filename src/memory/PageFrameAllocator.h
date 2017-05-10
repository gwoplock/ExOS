/*
 * PageFrameAllocator.h
 *
 *  Created on: Apr 29, 2017
 *      Author: garrett
 */

#ifndef PAGEFRAMEALLOCATOR_H_
#define PAGEFRAMEALLOCATOR_H_

#include "../global.h"
#include "mem.h"
#include "PageTable.h"
#include "../kernel.h"

class PageFrameAllocator {
	private:
		uint32_t lastUsedPage;
		uint8_t physPageAvalibility[(1024*1024)/8];
	public:
		PageFrameAllocator( );
		PageFrameAllocator(bool build);
		bool isAvalible(int page);
		void* allocatePhysMem(size_t sizeToAlloc);
		void* getNextVirtAddr(uint32_t sizeInPages);

};

#endif /* PAGEFRAMEALLOCATOR_H_ */