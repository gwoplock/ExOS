/*
 * maloc.h
 *
 *  Created on: Jul 3, 2017
 *      Author: garrett
 */

#ifndef MALLOC_H_
#define MALLOC_H_

#include "../global.h"
#include "PageTable.h"
#include "PageFrameAllocator.h"
#include "../kernel.h"

extern void* currentTop;
extern void* base;
extern uint32_t kernelEnd;

void mallocInit();
void* malloc(size_t size);

#endif /* MALLOC_H_ */
