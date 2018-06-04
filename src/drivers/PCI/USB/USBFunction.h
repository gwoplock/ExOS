#ifndef USB_Function_H_
#define USB_FUNCTION_H_

#include "drivers/generic/Device.h"
#include "hostController/USBHostController.h"
#include "USB_hubs/USBHubAbstract.h"
#include "USBConfiguration.h"


//TODO: we need a USB base class, to be made as I learn more
class USBFunction :public Device{
	protected:
	USBConfiguration** _configs;
	size_t _currnetConfig;
	uint8_t _address;
	//TODO check size
	int _maxDataSize;
	USBHostController _host;
	USBHubAbstract* _hub;
	public:
	USBFunction();
	USBFunction(USBHubAbstract* hub);

};

#endif