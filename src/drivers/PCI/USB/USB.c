/*
 * USB.c
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#include "drivers/PCI/USB/USB.h"
#include "drivers/PCI/PCI.h"

//TODO better host coontroller marking
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
	uint8_t progIF = getPCIProgIF(bus, device, function);
	switch (progIF){
		case 0x00:{
			//UHCI
			break;
		}
		case 0x10:{
			//OHCI
			break;
		}
		case 0x20:{
			//EHCI
			break;
		}
		case 0x30:{
			//XHCI
			break;
		}
		case 0x80:{
			//OTHER HCI
			break;
		}
		case 0xFE:{
			//Not a HCI
			break;
		}
		default:{
			//error
		}
	}
	//create correct object
	//store in array
	//mark as valid host controller 
}
