/*
 * PCICardBusDevice.h
 *
 *  Created on: Aug 16, 2017
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_PCI_PCIDEVICES_PCICARDBUSDEVICE_H_
#define SRC_DRIVERS_PCI_PCIDEVICES_PCICARDBUSDEVICE_H_

#include "drivers/PCI/PCI_devices/PCIDevice.h"
#include "Global.h"

class PCICardBusDevice: public PCIDevice {
	public:
		PCICardBusDevice( );
		PCICardBusDevice(uint8_t bus, uint8_t device, uint8_t function, bool page);
		virtual ~PCICardBusDevice( );
};

#endif /* SRC_DRIVERS_PCI_PCIDEVICES_PCICARDBUSDEVICE_H_ */
