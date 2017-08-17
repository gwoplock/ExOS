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
		uint32_t BAR0();
		uint32_t BAR1();
		uint32_t BAR2();
		uint32_t BAR3();
		uint32_t BAR4();
		uint32_t BAR5();
		uint32_t cardBusCISptr();
		uint16_t subsystemID();
		uint16_t subsystemVenderID();
		uint32_t expandROMbaseAddr();
		uint8_t capabilitiesPtr();
		uint8_t interruptLine();
		uint8_t interruptPin();
		uint8_t minGrant();
		uint8_t maxLatency();
};

#endif /* PCISTANDARDDEVICE_H_ */
