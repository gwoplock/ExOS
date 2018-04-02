/*
 * USB.h
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_PCI_USB_USB_H_
#define SRC_DRIVERS_PCI_USB_USB_H_

#include "Global.h"
//class USBController;

extern uint8_t maxUSBVersion;
//extern USBController* uSBControllers;

void USBInit();
void addUSBHostController(int bus, int device, int function);


#endif /* SRC_DRIVERS_PCI_USB_USB_H_ */
