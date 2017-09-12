/*
 * PCICardBusDevice.cpp
 *
 *  Created on: Aug 16, 2017
 *      Author: garrett
 */
#include "drivers/PCI/PCI_devices/PCICardBusDevice.h"
PCICardBusDevice::PCICardBusDevice( ) {
	// TODO Auto-generated constructor stub

}
PCICardBusDevice::PCICardBusDevice(uint8_t bus, uint8_t device, uint8_t function, bool page):PCIDevice(bus, device, function, page) {

}
PCICardBusDevice::~PCICardBusDevice( ) {
	// TODO Auto-generated destructor stub
}

