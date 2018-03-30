#ifndef USB_EHCI_ROOT_HUB_H_
#define USB_EHCI_ROOT_HUB_H_

#include "Global.h"
#include "USBHub.h"
#include "drivers/PCI/USB/hostController/USBEHCIController.h"
#include "utils/printf/Printf.h"
#include "Kernel.h"
#include "memory/structures/PageTable.h"
class USBEHCIRootHub : public USBHub {
    private:
        EHCIPortStatCont* _ports;
    public:
        USBEHCIRootHub():USBHub(){

        }
        USBEHCIRootHub(USBEHCIController* host):USBHub(host, true){
            pageTable.page((void*)(((uint32_t)(((USBEHCIController*)_host)->caps()->capLeng ))+ 0x44), (void*)(((uint32_t)(((USBEHCIController*)_host)->caps()->capLeng ))+ 0x44), 
                        sizeof(EHCIPortStatCont) * ((USBEHCIController*)_host)->caps()->structParams.numOfPorts );
            _ports = (EHCIPortStatCont*)(((uint32_t)(((USBEHCIController*)_host)->caps()->capLeng ))+ 0x44); //TODO add properly, CAPLENGTH (from host) + 44
            _portCount = ((USBEHCIController*)_host)->caps()->structParams.numOfPorts;
        }
        virtual void findDevices(){
            for (int i = 0; i < _portCount; i++){
                printf("found a device\n");
            }
        }
};

#endif