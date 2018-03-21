#ifndef USB_HUB_H_
#define USB_HUB_H_


#include "Global.h"
#include "drivers/PCI/USB/hostController/USBHostController.h"
//TODO superclass
class USBHub{
    protected:
        //TODO size
        int _portCount;
        USBHostController* _host; 
        USBHub(){

        }
        USBHub(USBHostController* host):_host(host){
            //TODO port count
        }
       USBHub(USBHostController* host, bool rootHubOnly):_host(host){
        }

};

#endif