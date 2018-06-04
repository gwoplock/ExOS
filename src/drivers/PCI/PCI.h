/*
 * PCI.h
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_PCI_PCI_H_
#define SRC_DRIVERS_PCI_PCI_H_

#include "Global.h"

extern uint8_t MAX_PCI_FUNCTIONS;
extern uint8_t MAX_PCI_DEVICES_PER_BUS;

struct ConfigAddress
{
	//uint8_t zero1 : 2;
	uint8_t registerNum : 6;
	uint8_t zero1 :2;
	uint8_t functionNum : 3;
	uint8_t deviceNum : 5;
	uint8_t busNum : 8;
	uint8_t zero2 : 7;
	uint8_t enable : 1;
} __attribute__((__packed__)) __attribute__((__may_alias__));

uint8_t getPCIProgIF(uint8_t bus, uint8_t device, uint8_t function);

uint32_t readPCIConfigWord(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset);

void enumPCIDevices();

uint16_t getPCIVender(uint8_t bus, uint8_t device, uint8_t function);

void checkPCIBus(uint8_t bus);

void checkPCIFunction(uint8_t bus, uint8_t device, uint8_t func);

uint16_t getPCIClass(uint8_t bus, uint8_t device, uint8_t func);

uint8_t getPCISecondBus(uint8_t bus, uint8_t device, uint8_t func);

#endif /* SRC_DRIVERS_PCI_PCI_H_ */
