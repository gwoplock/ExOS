/*
 * USB.c
 *
 *  Created on: Jul 12, 2017
 *      Author: garrett
 */

#include "USB.h"
#include "drivers/PCI/PCI.h"
#include "hostController/USBHostController.h"
#include "hostController/USBEHCIController.h"
#include "USB_hubs/USBHub.h"
#include "USB_hubs/USBEHCIRootHub.h"


USBHostController* usbControllers[3];
USBHub* testRoot;

void USBInit(){
	memSet(usbControllers, 3*sizeof(USBHostController*), 0);
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
			printf("          Is an EHCI controller\n");
			usbControllers[1] = new USBEHCIController(bus, device, function);
			testRoot=new USBEHCIRootHub((USBEHCIController*)usbControllers[1]);
			testRoot->findDevices();
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
}
