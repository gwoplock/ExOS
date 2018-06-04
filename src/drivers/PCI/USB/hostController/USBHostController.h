#ifndef USB_HOST_CONTROLLER_H_
#define USB_HOST_CONTROLLER_H_

#include "Global.h"
#include "drivers/PCI/PCI_devices/PCIStandardDevice.h"
#include "utils/printf/Printf.h"
//TODO superclass
class USBHostController : public PCIStandardDevice {
    protected:
    public:
        USBHostController(){

        }
        USBHostController(int bus, int device, int function):
        PCIStandardDevice(bus, device,function, true){
        }

};

#endif