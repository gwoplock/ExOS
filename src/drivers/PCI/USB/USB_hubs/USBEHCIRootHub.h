#ifndef USB_EHCI_ROOT_HUB_H_
#define USB_EHCI_ROOT_HUB_H_

#include "Global.h"
#include "USBHub.h"
#include "drivers/PCI/USB/hostController/USBEHCIController.h"
#include "utils/printf/Printf.h"
#include "Kernel.h"
#include "memory/structures/PageTable.h"
#include "drivers/timers/Sleep.h"
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
                if (_ports[i].conStat == 1){
                    printf("found a device\n");
                    printf("resetting device\n");
                    _ports[i].portEnable =0;
                    _ports[i].reset =1;
                    milisleep(80);
                    printf("done resetting\n");
                    _ports[i].reset = 0;
                    milisleep(5);
                    printf("port enabled\n");

                }
            }
        }
};

#endif