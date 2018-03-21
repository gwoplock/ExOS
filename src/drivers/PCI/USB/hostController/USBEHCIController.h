#ifndef USB_EHCI_CONTROLLER_H_
#define USB_EHCI_CONTROLLER_H_

#include "Global.h"
#include "USBHostController.h"
class USBEHCIController: public USBHostController{
    private:
    
    public:
        USBEHCIController(){

        }
        USBEHCIController(int bus, int device, int function) : USBHostController(bus,device,function){

        }
};

#endif