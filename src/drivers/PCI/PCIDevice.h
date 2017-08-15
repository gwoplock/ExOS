/*
 * PCIDevice.h
 *
 *  Created on: Jul 13, 2017
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_PCI_PCIDEVICE_H_
#define SRC_DRIVERS_PCI_PCIDEVICE_H_

#include "../../global.h"

class PCIDevice {
	private:
		uint8_t _bus;
		uint8_t _device;
		uint8_t _function;
		bool _page;
	public:
		PCIDevice( );
		PCIDevice(uint8_t bus, uint8_t device, uint8_t function, bool page);
};

#endif /* SRC_DRIVERS_PCI_PCIDEVICE_H_ */
