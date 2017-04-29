/*
 * mem.h
 *
 *  Created on: Apr 29, 2017
 *      Author: garrett
 */

#ifndef MEM_H_
#define MEM_H_

#include "../global.h"
#include "../kernel.h"
#include "../multiboot spec/multiboot.h"

struct MultibootMemoryMap{
	unsigned int size;
	uint64_t base_addr;
	uint64_t length;
	unsigned int type;
};

extern MultibootMemoryMap memMap[256];

void getMemMap(multiboot_info_t* mdb);

#endif /* MEM_H_ */
