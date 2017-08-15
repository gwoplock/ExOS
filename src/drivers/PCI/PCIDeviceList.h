/*
 * PCIDeviceList.h
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_PCI_PCIDEVICELIST_H_
#define SRC_DRIVERS_PCI_PCIDEVICELIST_H_

#include "../../global.h"
#include "PCI.h"
#include "PCIDevice.h"
#include "../../Utils/Linked_List/LinkedList.h"

class PCIDeviceList {
	private:
		size_t _size;
		LinkedList<PCIDevice*>* _list;
	public:
		PCIDeviceList( );
		PCIDeviceList(uint8_t BaseClass, uint8_t subClass, bool page);
		PCIDevice* toArray();
};

#endif /* SRC_DRIVERS_PCI_PCIDEVICELIST_H_ */
