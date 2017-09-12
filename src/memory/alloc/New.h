/*
 * New.h
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#ifndef NEW_H_
#define NEW_H_

#include "Global.h"

void * operator new(size_t size);
void operator delete(void * p);
void operator delete(void*, long unsigned int);
void* operator new[](unsigned long);


#endif /* NEW_H_ */
