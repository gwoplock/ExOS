/*
 * USB.c
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#include "drivers/PCI/USB/USB.h"

uint8_t maxUSBVersion = 0;
USBController* uSBControllers;

void USBInit(){//how it works:
//TODO:
	//enum USB controllers
		//Enum PCI devices
			//Enum PCI controllers (recrsive) |
				//Build list of controllers   |Already done by PCIInit
		//check if device is USB controller
	//fill USB controller array with controller objects
	//set max USB version
}

//todo types
void addUSBHostController(int bus, int device, int function){

}
