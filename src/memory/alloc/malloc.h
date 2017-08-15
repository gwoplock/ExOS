/*
 * maloc.h
 *
 *  Created on: Jul 3, 2017
 *      Author: garrett
 */

#ifndef MALLOC_H_
#define MALLOC_H_

#include "../../global.h"
#include "PageFrameAllocator.h"
#include "../../kernel.h"
#include "../structures/PageTable.h"

extern void* top;
extern void* base;
extern uint32_t kernelEnd;

void mallocInit();
#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif
void* malloc(size_t size);
void free(void *ptr);
#if defined(__cplusplus)
}/* Use C linkage for kernel_main. */
#endif
#endif /* MALLOC_H_ */
