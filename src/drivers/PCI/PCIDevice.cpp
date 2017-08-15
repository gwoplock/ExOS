/*
 * PCIDevice.cpp
 *
 *  Created on: Jul 13, 2017
 *      Author: garrett
 */

#include "PCIDevice.h"

PCIDevice::PCIDevice( ) {
	// TODO Auto-generated constructor stub

}
PCIDevice::PCIDevice(uint8_t bus, uint8_t device, uint8_t function, bool page) {
	_bus = bus;
	_device = device;
	_function = function;
	_page = page;
}

