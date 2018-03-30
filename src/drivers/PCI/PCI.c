/*
 * PCI.c
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#include "drivers/PCI/PCI.h"
#include "utils/printf/Printf.h"
#include "USB/USB.h"

uint8_t MAX_PCI_FUNCTIONS = 7;
uint8_t MAX_PCI_DEVICES_PER_BUS = 32;

uint8_t getPCIProgIF(uint8_t bus, uint8_t device, uint8_t function){
	auto progIF = readPCIConfigWord(bus, device, function, 0x08); 
	return (progIF>> 8) & 0xFFFF;
}

uint32_t readPCIConfigWord(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset)
{
	ConfigAddress addr;
	addr.enable = 1;
	//addr.zero1 = 0;
	addr.zero2 = 0;
	addr.registerNum = offset & 0xFC;
	addr.functionNum = function;
	addr.deviceNum = device;
	addr.busNum = bus;
	//printf("reading PCI register (new): %x\n", *(uint32_t *)&addr);
	outl(0xcf8, *(uint32_t *)&addr);
	//printf( "read %x", inl(0xCFC));
	return inl(0xCFC);
}

void enumPCIDevices()
{
	for (uint8_t func = 0; func <= MAX_PCI_FUNCTIONS; func++)
	{
		if (getPCIVender(0, 0, func) != 0xFFFF)
		{
			checkPCIBus(func);
		}
	}
}

uint16_t getPCIVender(uint8_t bus, uint8_t device, uint8_t function)
{
	return readPCIConfigWord(bus, device, function, 0) & 0xFFFF;
}

void checkPCIBus(uint8_t bus)
{
	printf("    Checking bus: %d\n", bus);
	for (uint8_t device = 0; device < MAX_PCI_DEVICES_PER_BUS; device++)
	{
		for (uint8_t func = 0; func < MAX_PCI_FUNCTIONS; func++)
		{
			if (getPCIVender(bus, device, func) != 0xFFFF)
			{
				checkPCIFunction(bus, device, func);
			}
		}
	}
}

void checkPCIFunction(uint8_t bus, uint8_t device, uint8_t func)
{
	asm("hlt");
	printf("      Found device at bus: %d, device: %d, func: %d\n", bus, device, func);
	printf("        The vender id is %x\n", getPCIVender(bus, device, func));
	uint32_t classCode = getPCIClass(bus, device, func);
	printf("        Has a class code of %x\n", classCode);
	uint8_t baseClass = (classCode >> 8) & 0xFF;
	uint8_t subClass = classCode & 0xFF;
	switch (baseClass)
	{
	case 0x06:
	{
		if (subClass == 0x04)
		{
			uint8_t secondBus = getPCISecondBus(bus, device, func);
			printf("        is a PCI->PCI with a 2nd bus of %d\n", secondBus);
			checkPCIBus(secondBus);
		}
		break;
	}
	case 0x0C:
	{
		if (subClass == 0x03){
			addUSBHostController(bus, device, func);
			printf("        This is a USB host controller\n");
			break;
		}
	}
	default:
	{
		printf("        This device is unkown\n");
		break;
	}
	}
}

uint16_t getPCIClass(uint8_t bus, uint8_t device, uint8_t func)
{
	return readPCIConfigWord(bus, device, func, 0x08)>>16;
}

uint8_t getPCISecondBus(uint8_t bus, uint8_t device, uint8_t func)
{
	return readPCIConfigWord(bus, device, func, 0x18) >> 8;
}