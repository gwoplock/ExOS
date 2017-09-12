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
 * top of the paged in mem
 */
extern void* top;
/**
 * base of free mem
 */
extern void* base;
/**
 * end of the kernel
 */
extern uint32_t kernelEnd;

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
#endif /* MALLOC_H_ */
