#ifndef USB_HUB_H_
#define USB_HUB_H_


#include "Global.h"
#include "drivers/PCI/USB/hostController/USBHostController.h"
#include "drivers/generic/SpecialDevice.h"
#include "utils/printf/Printf.h"

//TODO superclass
class USBHubAbstract :public SpecialDevice{
	protected:
		//TODO size
		int _portCount;
		USBHostController* _host; 
	public:
		USBHubAbstract():SpecialDevice(){

		}
		USBHubAbstract(USBHostController* host): _host(host){
			
		}
		virtual void findDevices()=0;

};

#endif