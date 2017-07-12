/*
 * New.h
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#ifndef NEW_H_
#define NEW_H_

#include "../../global.h"

void * operator new(size_t size);
void operator delete(void * p);
void operator delete(void*, long unsigned int);



#endif /* NEW_H_ */
