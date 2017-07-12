/*
 * USB.h
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_PCI_USB_USB_H_
#define SRC_DRIVERS_PCI_USB_USB_H_

#include "../../../global.h"
#include "USBController.h"

extern uint8_t maxUSBVersion;
extern USBController* uSBControllers;

void USBInit();


#endif /* SRC_DRIVERS_PCI_USB_USB_H_ */
