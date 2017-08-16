/*
 * PCIStandardDevice.cpp
 *
 *  Created on: Aug 16, 2017
 *      Author: garrett
 */

#include "PCIStandardDevice.h"

PCIStandardDevice::PCIStandardDevice( ) :
		PCIDevice( ) {
	// TODO Auto-generated constructor stub

}
PCIStandardDevice::PCIStandardDevice(uint8_t bus, uint8_t device, uint8_t function, bool page):PCIDevice(bus, device, function, page) {

}
PCIStandardDevice::~PCIStandardDevice( ) {
	// TODO Auto-generated destructor stub
}

