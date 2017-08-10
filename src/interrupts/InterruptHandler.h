/*
 * InterruptHnadler.h
 *
 *  Created on: Mar 1, 2017
 *      Author: garrett
 */

#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_

#include "../drivers/ProgrammableInterruptController.h"
#include "../kernel.h"

#include <errno.h>
#undef errno
extern int errno;

#define numOfSysCalls 22

#endif /* INTERRUPTHANDLER_H_ */
