/*
 * PCIStandardDevice.cpp
 *
 *  Created on: Aug 16, 2017
 *      Author: garrett
 */

#include "PCIStandardDevice.h"
#include "../PCI.h"

PCIStandardDevice::PCIStandardDevice( ) :
		PCIDevice( ) {
	// TODO Auto-generated constructor stub

}
PCIStandardDevice::PCIStandardDevice(uint8_t bus, uint8_t device, uint8_t function, bool page):PCIDevice(bus, device, function, page) {

}
PCIStandardDevice::~PCIStandardDevice( ) {
	// TODO Auto-generated destructor stub
}

uint32_t PCIStandardDevice::BAR0( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x10);
}

uint32_t PCIStandardDevice::BAR1( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x14);
}

uint32_t PCIStandardDevice::BAR2( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x18);
}

uint32_t PCIStandardDevice::BAR3( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x1C);
}

uint32_t PCIStandardDevice::BAR4( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x20);
}

uint32_t PCIStandardDevice::BAR5( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x24);
}

uint32_t PCIStandardDevice::cardBusCISptr( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x28);
}

uint16_t PCIStandardDevice::subsystemID( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x2C+16);
}

uint16_t PCIStandardDevice::subsystemVenderID( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x2c);
}

uint32_t PCIStandardDevice::expandROMbaseAddr( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x30);
}

uint8_t PCIStandardDevice::capabilitiesPtr( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x34);
}

uint8_t PCIStandardDevice::interruptLine( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x3c);
}

uint8_t PCIStandardDevice::interruptPin( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x3c+8);
}

uint8_t PCIStandardDevice::minGrant( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x3c+16);
}

uint8_t PCIStandardDevice::maxLatency( ) {
	return readPCIConfigWord(_bus, _device, _function, 0x3c+24);
}
