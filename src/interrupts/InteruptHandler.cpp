/*
 * InteruptHandler.c
 *
 *  Created on: Feb 27, 2017
 *      Author: garrett
 */

#include "InterruptHandler.h"



void (*syscalls[22])(
		void**) = {test, _exit, close, test, execve, fork, fstat,getpid, test, isatty, kill, link,lseek, open, read, sbrk, times, unlink, wait, write, getTimeOfDay, stat};

#if defined(__cplusplus)
extern "C" {/* Use C linkage for kernel_main. */
#endif

	void irq_handler(int line) {
		if (line == 1/*KB*/) {
			uint8_t scanCode = KB.getScancode( );
			uint8_t key = KB.getKey(scanCode);
			if (key != '\0' && ! (scanCode & 0x80)) {
				terminalPutChar(key);
			} else {
				terminalHandleSpecialKey(scanCode, KB.getModkeys( ));
			}
		}
		PIC_sendEOI(line);
	}

	void isr_handler(int interruptNumber) {
		terminalPutChar(' ');
		writeInt((uint32_t) interruptNumber);

	}

	void sysCallHandler(int sysCallNumber, void** args) {
		if (sysCallNumber > numOfSysCalls){
			 (*syscalls[sysCallNumber])(args);
		}
	}

#if defined(__cplusplus)
}
#endif

void test(void** args) {

}

void _exit(void** args) {

}
void close(void** args) {

}
void execve(void** args) {

}
void fork(void** args) {

}
void fstat(void** args) {

}
void getpid(void** args) {

}
void isatty(void** args) {

}
void kill(void** args) {

}
void link(void** args) {

}
void lseek(void** args) {

}
void open(void** args) {

}
void read(void** args) {

}
void sbrk(void** args) {

}
void times(void** args) {

}
void unlink(void** args) {

}
void wait(void** args) {

}
void write(void** args) {

}
void getTimeOfDay(void** args) {

}
void stat(void** args) {

}
