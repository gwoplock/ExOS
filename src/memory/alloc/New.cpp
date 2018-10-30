/*
 * New
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#include "memory/alloc/New.h"
#include "utils/printf/Printf.h"
#include <stddef.h>
 
void *operator new(size_t size)
{
    return malloc(size);
}
 
void *operator new[](size_t size)
{
    return malloc(size);
}
 
void operator delete(void* p, unsigned long size){

}

void operator delete(void *p)
{
    free(p);
}
 
void operator delete[](void *p)
{
    free(p);
}
void operator delete [](void* p, long unsigned int size){

}