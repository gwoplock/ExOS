/*
 * PCI.c
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#include "PCI.h"

//TODO clean up a lot

uint8_t MAX_PCI_FUNCTION = 8;

bool validPCIBuses[256];

void PCIInit( ) {
	for (uint16_t i = 0; i < 256; i++){
		validPCIBuses[i] = false;
	}
	//bus, slot, function
	if (isPCIMultiFunctionDevice(0, 0, 0)) {
		for (uint8_t function = 0; function < MAX_PCI_FUNCTION; function++) {
			if ( !isValidPCIFunction(0, 0, function)) {
				break;
			}
			checkPCIBus(function);
		}
	} else {
		checkPCIBus(0);
	}
}

bool isPCIMultiFunctionDevice(uint8_t bus, uint8_t device, uint8_t function) {
	return ! ( (getPCIHeaderType(bus, device, function) & 0x80) == 0);
}

bool isValidPCIFunction(uint8_t bus, uint8_t device, uint8_t function) {
	return getPCIVenderID(bus, device, function) != 0xFFFF;
}

uint16_t getPCIVenderID(uint8_t bus, uint8_t slot, uint8_t function) {
	return readPCIConfigWord(bus, slot, function, 0);
}

uint16_t readPCIConfigWord(uint8_t bus, uint8_t slot, uint8_t func,
		uint8_t offset) {
	uint32_t address;
	uint32_t lbus = (uint32_t) bus;
	uint32_t lslot = (uint32_t) slot;
	uint32_t lfunc = (uint32_t) func;
	uint16_t tmp = 0;

	address = (uint32_t)(
			(lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc)
					| ((uint32_t) 0x80000000));

	outl(0xCF8, address);
	tmp = (uint16_t)( (inl(0xCFC) >> ( (offset & 2) * 8)) & 0xffff);
	return (tmp);
}

void checkPCIBus(uint8_t bus) {
	uint8_t device;
	validPCIBuses[bus] = true;
	for (device = 0; device < 32; device++) {
		checkPCIDevice(bus, device);
	}
}

void checkPCIFunction(uint8_t bus, uint8_t device, uint8_t function) {
	uint8_t baseClass;
	uint8_t subClass;
	uint8_t secondaryBus;

	baseClass = getPCIBaseClass(bus, device, function);
	subClass = getPCISubClass(bus, device, function);
	if ( (baseClass == 0x06) && (subClass == 0x04)) {
		secondaryBus = getPCISecondaryBus(bus, device, function);
		checkPCIBus(secondaryBus);
	}
}

void checkPCIDevice(uint8_t bus, uint8_t device) {
	uint8_t function = 0;

	uint16_t vendorID = getPCIVenderID(bus, device, function);
	if (vendorID == 0xFFFF)
		return;        // Device doesn't exist
	checkPCIFunction(bus, device, function);
	uint8_t headerType = getPCIHeaderType(bus, device, function);
	if ( (headerType & 0x80) != 0) {
		/* It is a multi-function device, so check remaining functions */
		for (function = 1; function < 8; function++) {
			if (getPCIVenderID(bus, device, function) != 0xFFFF) {
				checkPCIFunction(bus, device, function);
			}
		}
	}
}
uint8_t getPCIBaseClass(uint8_t bus, uint8_t device, uint8_t function){
	return readPCIConfigWord(bus,device,function,0xB);
}

uint8_t getPCISubClass(uint8_t bus, uint8_t device, uint8_t function){
	return readPCIConfigWord(bus,device,function,0xA);
}

uint8_t getPCIHeaderType(uint8_t bus, uint8_t device, uint8_t function){
	return readPCIConfigWord(bus,device,function,0xE);
}

uint8_t getPCISecondaryBus(uint8_t bus, uint8_t device, uint8_t function){
	return readPCIConfigWord(bus,device,function, 0x19);
}

