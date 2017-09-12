/*
 * PCIDevice.h
 *
 *  Created on: Jul 13, 2017
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_PCI_PCIDEVICE_H_
#define SRC_DRIVERS_PCI_PCIDEVICE_H_

#include "Global.h"


class PCIDevice {
	protected:
		uint8_t _bus;
		uint8_t _device;
		uint8_t _function;
		bool _page;
	public:
		PCIDevice( );
		PCIDevice(uint8_t bus, uint8_t device, uint8_t function, bool page);
		virtual ~PCIDevice( ){

		}
		uint16_t deviceID();
		uint16_t venderID();
		uint16_t status();
		uint16_t command();
		void command(uint16_t com);
		uint8_t classCode();
		uint8_t subClassCode();
		uint8_t progIF();
		uint8_t revisionID();
		uint8_t BIST();
		void BIST(uint8_t);
		uint8_t headerType();
		uint8_t latencyTimer();
		uint8_t cacheLineSize();
		void cacheLineSize(uint8_t);
};

#endif /* SRC_DRIVERS_PCI_PCIDEVICE_H_ */
