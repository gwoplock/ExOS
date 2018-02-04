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
#include "memory/alloc/Malloc.h"
#include "memory/alloc/New.h"
#include "clib_misc/Abort.h"
#include "clib_misc/Assert.h"
#include "memory/Mem.h"

//bochs breakpoing ASM
#define BREAKPOINT asm("xchgw %%bx, %%bx" : : : "%bx");

//helpful constant
#define FOUR_KB 4096


#endif /* GLOBAL_H_ */
