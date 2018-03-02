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
	return (readPCIConfigWord(bus, device, function, 0x08) >> 8) & 0xFFFF;
}

//TODO rewrite
/**
 * read 32 bits from PCI config space
 * @param bus
 * @param slot
 * @param func
 * @param offset into config space
 * @return uint32 of the config space starting at offset.
 */
/*uint32_t readPCIConfigWord(uint8_t bus, uint8_t slot, uint8_t func,
						   uint8_t offset)
{
	uint32_t address;
	uint32_t lbus = (uint32_t)bus;
	uint32_t lslot = (uint32_t)slot;
	uint32_t lfunc = (uint32_t)func;
	uint16_t tmp = 0;

	/* create configuration address as per Figure 1 
	address = (uint32_t)((lbus << 16) | (lslot << 11) |
						 (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

	/* write out the address 
	//printf("reading PCI register (old): %x\n", address);
	outl(0xCF8, address);
	/* read in the data 
	/* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register 
	tmp = (uint16_t)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
	return (tmp);
}*/

uint32_t readPCIConfigWord/*New*/(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset)
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
	//printf("old: 0x%x, new: 0x%x", readPCIConfigWord(0,2,4,8), readPCIConfigWordNew(0,2,4,8) );
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
	}
	case 0x0C:
	{
		if (subClass == 0x03){
			addUSBHostController(bus, device, func);
			printf("        This is a USB host controller\n");
		}
		break;
	}
	default:
	{
		printf("        This device is unkown\n");
		break;
	}
	}
	/*if (classCode == 0x604)
	{
		uint8_t secondBus = getPCISecondBus(bus, device, func);
		printf("        is a PCI->PCI with a 2nd bus of %d\n", secondBus);
			checkPCIBus(secondBus);
	}*/
}

uint16_t getPCIClass(uint8_t bus, uint8_t device, uint8_t func)
{
	return readPCIConfigWord(bus, device, func, 0x08)>>16;
}

uint8_t getPCISecondBus(uint8_t bus, uint8_t device, uint8_t func)
{
	return readPCIConfigWord(bus, device, func, 0x18) >> 8;
}

/*
//TODO clean up a lot


/**
 * bool array of valid PCI buses
 
bool validPCIBuses[256];
/**
 * inits the PCI sub system. finds all PCI buses
 
void PCIInit( ) {
	//make sure all buses are invalid
	for (uint16_t i = 0; i < 256; i++){
		validPCIBuses[i] = false;
	}
	//check if the first bus multifunction, if so check each function for buses.
	if (isPCIMultiFunctionDevice(0, 0, 0)) {
		for (uint8_t function = 0; function < MAX_PCI_FUNCTION; function++) {
			if ( !isValidPCIFunction(0, 0, function)) {
				break;
			}
			//check the valid function
			checkPCIBus(function);
		}
	} else {
		//check the base function if not multifunction
		checkPCIBus(0);
	}
}
/**
 * checks if the device is multifunction based on given function header type
 * @param bus device is on
 * @param device on bus
 * @param function in device
 * @return if device is multifunction
 
bool isPCIMultiFunctionDevice(uint8_t bus, uint8_t device, uint8_t function) {
	return ! ( (getPCIHeaderType(bus, device, function) & 0x80) == 0);
}
/**
 * checks validity of function based off vender code
 * @param bus
 * @param device
 * @param function
 * @return if the function is a valid function
 
bool isValidPCIFunction(uint8_t bus, uint8_t device, uint8_t function) {
	return getPCIVenderID(bus, device, function) != 0xFFFF;
}
/**
 * checks the vender of the pci device / function
 * @param bus
 * @param slot
 * @param function
 * @return vender ID
 
uint16_t getPCIVenderID(uint8_t bus, uint8_t slot, uint8_t function) {
	return readPCIConfigWord(bus, slot, function, 0);
}

/**
 * check devices on bus for other buses
 * @param bus
 
void checkPCIBus(uint8_t bus) {
	uint8_t device;
	//set that its a valid bus
	validPCIBuses[bus] = true;
	//check the devices on the bus
	for (device = 0; device < 32; device++) {
		checkPCIDevice(bus, device);
	}
}
/**
 * check device / function if it's a PCI bus
 * @param bus
 * @param device
 * @param function
 
void checkPCIFunction(uint8_t bus, uint8_t device, uint8_t function) {
	uint8_t baseClass;
	uint8_t subClass;
	uint8_t secondaryBus;
	//get the class codes
	baseClass = getPCIBaseClass(bus, device, function);
	subClass = getPCISubClass(bus, device, function);
	//check the class codes to see if it's a bus
	if ( (baseClass == 0x06) && (subClass == 0x04)) {
		//check that bus
		secondaryBus = getPCISecondaryBus(bus, device, function);
		checkPCIBus(secondaryBus);
	}
}
/**
 * check device's functions to see if it holds a bus
 * @param bus
 * @param device
 
void checkPCIDevice(uint8_t bus, uint8_t device) {
	uint8_t function = 0;

	uint16_t vendorID = getPCIVenderID(bus, device, function);
	if (vendorID == 0xFFFF)
		return;        // Device doesn't exist
	checkPCIFunction(bus, device, function);
	uint8_t headerType = getPCIHeaderType(bus, device, function);
	if ( (headerType & 0x80) != 0) {
		/* It is a multi-function device, so check remaining functions 
		for (function = 1; function < 8; function++) {
			if (getPCIVenderID(bus, device, function) != 0xFFFF) {
				checkPCIFunction(bus, device, function);
			}
		}
	}
}
/**
 * read the PCI base class from the config space
 * @param bus
 * @param device
 * @param function
 * @return base class
 
uint8_t getPCIBaseClass(uint8_t bus, uint8_t device, uint8_t function){
	return readPCIConfigWord(bus,device,function,0xB);
}
/**
 * read the PCI sub class from the config space
 * @param bus
 * @param device
 * @param function
 * @return sub class
 
uint8_t getPCISubClass(uint8_t bus, uint8_t device, uint8_t function){
	return readPCIConfigWord(bus,device,function,0xA);
}
/**
 * read the PCI header type from the config space
 * @param bus
 * @param device
 * @param function
 * @return header type
 
uint8_t getPCIHeaderType(uint8_t bus, uint8_t device, uint8_t function){
	return readPCIConfigWord(bus,device,function,0xE);
}
/**
 * read the PCI second bus from the config space for pci bridge devices
 * @param bus
 * @param device
 * @param function
 * @return secondary bus
 
uint8_t getPCISecondaryBus(uint8_t bus, uint8_t device, uint8_t function){
	return readPCIConfigWord(bus,device,function, 0x19);
}

*/