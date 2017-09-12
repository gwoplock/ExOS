/*
 * PCIDeviceList.cpp

 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#include "drivers/PCI/PCIDeviceList.h"
#include "drivers/PCI/PCI.h"
#include "drivers/PCI/PCI_devices/PCIStandardDevice.h"
#include "drivers/PCI/PCI_devices/PCIBridgeDevice.h"
#include "drivers/PCI/PCI_devices/PCICardBusDevice.h"
#include "drivers/TTY/Console.h"

PCIDeviceList::PCIDeviceList( ) {
	_list = new LinkedList<PCIDevice*>;
	_size = 0;
}
//TODO comment and fix
PCIDeviceList::PCIDeviceList(uint8_t baseClass, uint8_t subClass, bool page) {
	(void) page;
	_list = new LinkedList<PCIDevice*>;
	_size = 0;
BREAKPOINT
	for (int i = 0; i < 256; i++) {
		if (validPCIBuses[i]) {
			BREAKPOINT
			writeInt(i);
			BREAKPOINT
			for (int k = 0; k < 32; k++) {
				if (isPCIMultiFunctionDevice(i, k, 0)) {
					for (int n = 0; n < 8; n++) {
						if (isValidPCIFunction(i, k, n)) {
							if (getPCIBaseClass(i, k, n) == baseClass
									&& getPCISubClass(i, k, n) == subClass) {
								PCIDevice* toAdd = nullptr;
								switch (getPCIHeaderType(i, k, n) & 0x7F) {
									case 0x0 : {
										toAdd = new PCIStandardDevice(i, k, n,
												false);
										break;
									}
									case 0x1 : {
										toAdd = new PCIBridgeDevice(i, k, n,
												false);
										break;
									}
									case 0x2 : {
										toAdd = new PCICardBusDevice(i, k,
												n, false);
									}
									default : {

									}
								}
								if(toAdd != nullptr){
								_list->add(toAdd);
								_size++;
								} else {
									//well fuck.
									//TODO handle errors...
								}
							}
						}
					}
				} else {
					if (isValidPCIFunction(i, k, 0)) {
						if (getPCIBaseClass(i, k, 0) == baseClass
								&& getPCISubClass(i, k, 0) == subClass) {
							PCIDevice* toAdd =nullptr;
							switch (getPCIHeaderType(i, k, 0) & 0x7F) {
								case 0x0 : {
									toAdd = new PCIStandardDevice(i, k, 0,
											false);
									break;
								}
								case 0x1 : {
									toAdd = new PCIBridgeDevice(i, k, 0, false);
									break;
								}
								case 0x2 : {
									toAdd = new PCICardBusDevice(i, k, 0,
											false);
								}
								default : {

								}
							}
							_list->add(toAdd);
							_size++;
						}
					}
				}
			}
		}
	}
}

PCIDevice** PCIDeviceList::toArray( ) {
	//make array of PCIDevice*
	PCIDevice** listArr = new PCIDevice*[_size];
	//go through array and add each to the array
	auto current = _list->head( );
	for (unsigned int i = 0; i < _size; i++) {
		listArr[i] = current->data( );
		current = current->next( );
	}
	return listArr;
}
