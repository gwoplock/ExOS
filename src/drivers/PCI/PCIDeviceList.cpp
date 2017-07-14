/*
 * PCIDeviceList.cpp

 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#include "PCIDeviceList.h"

PCIDeviceList::PCIDeviceList( ) {
	LinkedList<PCIDevice*> _list;
	_size =0;
}

PCIDeviceList::PCIDeviceList(uint8_t baseClass, uint8_t subClass) {
	LinkedList<PCIDevice*> _list;
	_size=0;
	for (int i = 0; i < 256; i++) {
		if (validPCIBuses[i]) {
			for (int k = 0; k < 32; k++) {
				if (isPCIMultiFunctionDevice(i, k, 0)) {
					for (int n = 0; n < 8; n++) {
						if (isValidPCIFunction(i, k, n)) {
							if (getPCIBaseClass(i, k, n) == baseClass
									&& getPCISubClass(i, k, n) == subClass) {
								//todo get the correct object for the device
								_list.add(new PCIDevice());
								_size++;
							}
						}
					}
				} else {
					if (isValidPCIFunction(i, k, 0)) {
						if (getPCIBaseClass(i, k, 0) == baseClass
								&& getPCISubClass(i, k, 0) == subClass) {
							//todo get the correct object for the device
							_list.add(new PCIDevice());
							_size++;
						}
					}
				}
			}
		}
	}
}
