/*
 * USBController.h
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#ifndef USBCONTROLLER_H_
#define USBCONTROLLER_H_

#include "Global.h"
#include "drivers/PCI/PCI_devices/PCIStandardDevice.h"

class USBController :public PCIStandardDevice{
	public:
		USBController( );
};

#endif /* USBCONTROLLER_H_ */
