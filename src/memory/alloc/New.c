/*
 * New
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#include "New.h"

void * operator new(size_t size) {
	//just call malloc, the compiler will run the constructor automaticly
	void * p = malloc(size);
	return p;
}

void operator delete(void * p) {
//TODO
}
void operator delete(void* ptr, long unsigned int size/*maybe?*/) {
//TODO
}

void* operator new[](unsigned long size){
	//new for arrays, ame as the other new
	void * p = malloc(size);
	return p;
}
