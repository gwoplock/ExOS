#ifndef USB_EHCI_ROOT_HUB_H_
#define USB_EHCI_ROOT_HUB_H_

#include "Global.h"
#include "USBHub.h"
#include "drivers/PCI/USB/hostController/USBEHCIController.h"



class USBEHCIRootHub : public USBHub {
    private:
        EHCIPortStatCont* _ports;
    public:
        USBEHCIRootHub():USBHub(){

        }
        USBEHCIRootHub(USBEHCIController* host):USBHub(host, true){
            _ports = (EHCIPortStatCont*)(_host->BAR0() + 0); //TODO add properly, CAPLENGTH (from host) + 44
            //TODO get port count from _host

        }
};

#endif