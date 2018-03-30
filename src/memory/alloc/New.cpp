/*
 * New
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#include "memory/alloc/New.h"
#include "utils/printf/Printf.h"
//TODO fix this file

void * operator new(size_t size) {
	//just call malloc, the compiler will run the constructor automaticly
	printf("called new\n");
	//void * p = /*malloc(size);*/ ::operator new(size);
	return malloc(size);
}

void operator delete(void * p) {
	free(p);
}
void operator delete(void* ptr, long unsigned int size/*maybe?*/) {
	(void) size;
	free(ptr);
}

void* operator new[](unsigned long size){
	//new for arrays, ame as the other new
	void * p = malloc(size);
	return p;
}
