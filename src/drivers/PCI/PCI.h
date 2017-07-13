/*
 * PCI.h
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_PCI_PCI_H_
#define SRC_DRIVERS_PCI_PCI_H_

#include "../../global.h"

extern int8_t MAX_PCI_FUNCTIONS;
extern bool validPCIBuses[256];

void PCIInit( );
bool isPCIMultiFunctionDevice(uint8_t bus, uint8_t device, uint8_t function);
bool isValidPCIFunction(uint8_t bus, uint8_t device, uint8_t function);
uint16_t getPCIVenderID(uint8_t bus, uint8_t slot, uint8_t function);
uint16_t readPCIConfigWord(uint8_t bus, uint8_t slot, uint8_t func,
		uint8_t offset);
void checkPCIBus(uint8_t bus);
void checkPCIFunction(uint8_t bus, uint8_t device, uint8_t function);
void checkPCIDevice(uint8_t bus, uint8_t device);
uint8_t getPCIBaseClass(uint8_t bus, uint8_t device, uint8_t function);
uint8_t getPCISubClass(uint8_t bus, uint8_t device, uint8_t function);
uint8_t getPCIHeaderType(uint8_t bus, uint8_t device, uint8_t function);
uint8_t getPCISecondaryBus(uint8_t bus, uint8_t device, uint8_t function);

#endif /* SRC_DRIVERS_PCI_PCI_H_ */
