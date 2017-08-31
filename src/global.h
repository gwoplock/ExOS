/*
 * global.h
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_


#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "AsmHelper.h"
#include "memory/alloc/malloc.h"
#include "memory/alloc/New.h"
#include "cLibMisc/abort.h"

//bochs breakpoing ASM
#define BREAKPOINT asm("xchgw %%bx, %%bx" : : : "%bx");
//paging info
#define KernelPageDirStart 768
#define KernelPageStart 786432
//helpful constant
#define fourKb 4096


#endif /* GLOBAL_H_ */
