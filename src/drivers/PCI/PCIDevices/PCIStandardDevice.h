/*
 * PCIStandardDevice.h
 *
 *  Created on: Aug 16, 2017
 *      Author: garrett
 */

#ifndef PCISTANDARDDEVICE_H_
#define PCISTANDARDDEVICE_H_

#include "PCIDevice.h"

class PCIStandardDevice: public PCIDevice {
	public:
		PCIStandardDevice( );
		PCIStandardDevice(uint8_t bus, uint8_t device, uint8_t function, bool page);
		virtual ~PCIStandardDevice( );
};

#endif /* PCISTANDARDDEVICE_H_ */
