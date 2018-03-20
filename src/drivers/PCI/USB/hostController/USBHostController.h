#ifndef USB_HOST_CONTROLLER_H_
#define USB_HOST_CONTROLLER_H_

#include "Global.h"

//TODO superclass
class USBHostController {
    private:
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