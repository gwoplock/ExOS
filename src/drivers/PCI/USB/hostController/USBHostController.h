#ifndef USB_HOST_CONTROLLER_H_
#define USB_HOST_CONTROLLER_H_

#include "Global.h"
#include "drivers/PCI/PCI_devices/PCIStandardDevice.h"

//TODO superclass
class USBHostController : public PCIStandardDevice {
    protected:
        uint8_t _bus;
        uint8_t _device;
        uint8_t _function;
    public:
        USBHostController(){

        }
        USBHostController(int bus, int device, int function){
            _bus= bus;
            _device = device;
            _function = function;
        }

};

#endif