/*
 * PCIDevice.cpp
 *
 *  Created on: Jul 13, 2017
 *      Author: garrett
 */

#include "drivers/PCI/PCI_devices/PCIDevice.h"
#include "drivers/PCI/PCI.h"

PCIDevice::PCIDevice()
{
	// TODO Auto-generated constructor stub
}
PCIDevice::PCIDevice(uint8_t bus, uint8_t device, uint8_t function, bool page)
{
	_bus = bus;
	_device = device;
	_function = function;
	_page = page;
}

uint16_t PCIDevice::deviceID()
{
	return readPCIConfigWord(_bus, _device, _function, 0x00) >> 16;
}

uint16_t PCIDevice::venderID()
{
	return readPCIConfigWord(_bus, _device, _function, 0);
}

uint16_t PCIDevice::status()
{
	return readPCIConfigWord(_bus, _device, _function, 0x04) >> 16;
}

uint16_t PCIDevice::command()
{
	return readPCIConfigWord(_bus, _device, _function, 0x04);
}

void PCIDevice::command(uint16_t com)
{
	//(void)com;
}

uint8_t PCIDevice::classCode()
{
	return readPCIConfigWord(_bus, _device, _function, 0x08) >> 24;
}

uint8_t PCIDevice::subClassCode()
{
	return readPCIConfigWord(_bus, _device, _function, 0x08) >> 16;
}

uint8_t PCIDevice::progIF()
{
	return readPCIConfigWord(_bus, _device, _function, 0x08) >> 8;
}

uint8_t PCIDevice::revisionID()
{
	return readPCIConfigWord(_bus, _device, _function, 0x08);
}

uint8_t PCIDevice::BIST()
{
	return readPCIConfigWord(_bus, _device, _function, 0x0c) >> 24;
}

void PCIDevice::BIST(uint8_t testCode)
{
	//(void) testCode;
}

uint8_t PCIDevice::headerType()
{
	return readPCIConfigWord(_bus, _device, _function, 0x0c) >>16;
}

uint8_t PCIDevice::latencyTimer()
{
	return readPCIConfigWord(_bus, _device, _function, 0x0c) >>8;
}

uint8_t PCIDevice::cacheLineSize()
{
	return readPCIConfigWord(_bus, _device, _function, 0x0c);
}

void PCIDevice::cacheLineSize(uint8_t lineSize)
{
	//(void) lineSize;
}
