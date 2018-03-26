#ifndef USB_HUB_H_
#define USB_HUB_H_


#include "Global.h"
#include "drivers/PCI/USB/hostController/USBHostController.h"
#include "drivers/generic/SpecialDevice.h"
//TODO superclass
class USBHub :public SpecialDevice{
    protected:
        //TODO size
        int _portCount;
        USBHostController* _host; 
    public:
        USBHub(){

        }
        USBHub(USBHostController* host):_host(host){
            //TODO port count
        }
        USBHub(USBHostController* host, bool rootHubOnly):_host(host){
           (void) rootHubOnly;

        }
        virtual void findDevices(){

        }

};

#endif