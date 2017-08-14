/*
 * InteruptHandler.c
 *
 *  Created on: Feb 27, 2017
 *      Author: garrett
 */

#include "InterruptHandler.h"

void* scratchSpace = 0xFFFFF000;

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
		if (sysCallNumber > numOfSysCalls) {
			( *syscalls[sysCallNumber])(args);
		}
	}


//this is probly bad practice... oh well
#define return *scratchSpace =

void test(void** args) {
//do nothing. its a test
}

void _exit(void** args) {
//TODO
}
void close(void** args) {
	return - 1;
}
void execve(void** args) {
	errno = ENOMEM;
	return - 1;
}
void fork(void** args) {
	errno = EAGAIN;
	return - 1;
}
//TODO fix
void fstat(void** args) {
	int file = * ((int*) args[0]);
	struct stat *st = (struct stat*) args[1];
	st->st_mode = S_IFCHR;
	return 0 ;
}
void getpid(void** args) {
	return 1 ;
}
void isatty(void** args) {
	return 1 ;
}
void kill(void** args) {
	errno = EINVAL;
	return - 1;
}
void link(void** args) {
	errno = EMLINK;
	return - 1;
}
void lseek(void** args) {
	return 0 ;
}
void open(void** args) {
	return - 1;
}
void read(void** args) {
	return 0 ;
}
void sbrk(void** args) {
	//TODO this only works for the kernel.
	int incr = *((int*) args[0]);
	void* startOfNewMem = frameAlloc.allocatePhysMem(incr, pageTable.getKernelStart());
	return startOfNewMem;
}
void times(void** args) {
	return - 1;
}
void unlink(void** args) {
	errno = ENOENT;
	return - 1;
}
void wait(void** args) {
	errno = ECHILD;
	return - 1;
}
void write(void** args) {
	int file = * ((int*) args[0]);
	char * string = (char *) args[1];
	int length = * ((int*) args[2]);
	if (file == 1){
		terminalWrite(string, length);
	}
}
void getTimeOfDay(void** args) {

}
void stat(void** args) {
	char* file = (char *) args[0];
	struct stat *st = (struct stat*) args[1];
	st->st_mode = S_IFCHR;
	return 0 ;
}
#undef return

#if defined(__cplusplus)
}
#endif
