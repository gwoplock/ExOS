/*
 * maloc.h
 *
 *  Created on: Jul 3, 2017
 *      Author: garrett
 */

#ifndef MALLOC_H_
#define MALLOC_H_

#include "Global.h"

/**
 * end of the kernel
 */
extern uint32_t kernelEnd;

struct memHeader{
	bool used;
	memHeader *next;
};

/**
 * set up the vars needed for malloc
 */
void mallocInit();
#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif

	/**
	 *  mem alloc
	 * @param size to alloc
	 */
void* malloc(size_t size);

/**
 * free mem
 * @param ptr to the mem to free
 */
void free(void *ptr);

#if defined(__cplusplus)
}/* Use C linkage for kernel_main. */
#endif

void compFreeSpace();

void *realloc(void *ptr, size_t size);

#endif /* MALLOC_H_ */
