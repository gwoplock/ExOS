/*
 * PCIBridgeDevice.h
 *
 *  Created on: Aug 16, 2017
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_PCI_PCIDEVICES_PCIBRIDGEDEVICE_H_
#define SRC_DRIVERS_PCI_PCIDEVICES_PCIBRIDGEDEVICE_H_

#include "PCIDevice.h"

class PCIBridgeDevice: public PCIDevice {
	public:
		PCIBridgeDevice( );
		PCIBridgeDevice(uint8_t bus, uint8_t device, uint8_t function, bool page);
		virtual ~PCIBridgeDevice( );
};

#endif /* SRC_DRIVERS_PCI_PCIDEVICES_PCIBRIDGEDEVICE_H_ */
