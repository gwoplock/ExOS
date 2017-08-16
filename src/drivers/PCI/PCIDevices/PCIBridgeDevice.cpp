/*
 * PCIBridgeDevice.cpp
 *
 *  Created on: Aug 16, 2017
 *      Author: garrett
 */
#include "PCIBridgeDevice.h"
PCIBridgeDevice::PCIBridgeDevice( ) {
	// TODO Auto-generated constructor stub

}
PCIBridgeDevice::PCIBridgeDevice(uint8_t bus, uint8_t device, uint8_t function, bool page):PCIDevice(bus, device, function, page) {

}

PCIBridgeDevice::~PCIBridgeDevice( ) {
	// TODO Auto-generated destructor stub
}

