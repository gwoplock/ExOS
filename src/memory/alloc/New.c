/*
 * New
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#include "New.h"

void * operator new(size_t size) {

	void * p = malloc(size);
	return p;
}

void operator delete(void * p) {

}
void operator delete(void* ptr, long unsigned int size/*maybe?*/) {

}

void* operator new[](unsigned long size){
	void * p = malloc(size);
	return p;
}
