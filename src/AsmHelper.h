/*
 * asmHelper.h
 *
 *  Created on: Sep 20, 2016
 *      Author: garrett
 */

#ifndef ASMHELPER_H_
#define ASMHELPER_H_

#include "global.h"

static inline uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile ( "inb %1, %0"
			: "=a"(ret)
			: "Nd"(port) );
	return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
	asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );

}

static inline uint32_t inl(uint16_t port) {
	uint32_t ret;
	asm volatile ( "inl %1, %0"
			: "=a"(ret)
			: "Nd"(port) );
	return ret;
}

static inline void outl(uint16_t port, uint32_t val) {
	asm volatile ( "outl %0, %1" : : "a"(val), "Nd"(port) );

}

static inline void io_wait(void)
{
    asm volatile ( "jmp 1f\n\t"
                   "1:jmp 2f\n\t"
                   "2:" );
}


#endif /* ASMHELPER_H_ */
