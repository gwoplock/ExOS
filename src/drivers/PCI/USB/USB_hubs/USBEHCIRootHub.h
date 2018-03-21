#ifndef USB_EHCI_ROOT_HUB_H_
#define USB_EHCI_ROOT_HUB_H_

#include "Global.h"
#include "USBHub.h"
#include "drivers/PCI/USB/hostController/USBEHCIController.h"
struct EHCIPortStatCont{
    uint8_t conStat:1;
    uint8_t conStatChange:1;
    uint8_t portEnable:1;
    uint8_t portEnableChange:1;
    uint8_t overCurrent:1;
    uint8_t overCurrentChage:1;
    uint8_t forceResume:1;
    uint8_t suspend:1;
    uint8_t reset:1;
    uint8_t reserved1:1;
    uint8_t lineStat:2;
    uint8_t power:1;
    uint8_t owner:1;
    uint8_t indicatorCont:2;
    uint8_t testCont:4;
    uint8_t wakeOnConnect:1;
    uint8_t wakeOnDisconnect:1;
    uint8_t wakeOnOvercurrent:1;
    uint8_t reserved2;
};

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