#ifndef USB_EHCI_CONTROLLER_H_
#define USB_EHCI_CONTROLLER_H_

#include "Global.h"
#include "USBHostController.h"

struct HWVersion{
    uint8_t major;
    uint8_t minor;
};
struct HWStrucParams{
    uint8_t numOfPorts:4;
    uint8_t ppc:1;
    uint8_t reserved1:2;
    uint8_t portRouteRules:1;
    uint8_t numOfPortsPerCompanionController:4;
    uint8_t numOfCompanionControllers:4;
    uint8_t portIndicator:1;
    uint8_t reserved2:3;
    uint8_t debugPortNum:4;
    uint8_t reserved3;
};

struct HWCapParams{
    uint8_t addrCap:1;
    uint8_t progFrameListFlag:1;
    uint8_t asyncSchedParkCap:1;
    uint8_t reserved1:1;
    uint8_t isochornousSchedThersh:4;
    uint8_t ehciExtendCapsPtr;
    uint16_t reserved2;
};

struct CompaninoPortRoute{
    //TODO.... 15 nibble array
};

struct CapReg{
    uint8_t capLeng;
    uint8_t reserved;
    HWVersion hwVersion;
    HWStrucParams structParams;
    HWCapParams capParams;
    CompaninoPortRoute portRoute;
};

struct operReg{
//TODO 
};


class USBEHCIController: public USBHostController{
    private:
        CapReg* _caps;
        operReg* _oper;
    public:
        USBEHCIController(){

        }
        USBEHCIController(int bus, int device, int function) : USBHostController(bus,device,function){
            _caps = (CapReg*)BAR0();
            _oper = (operReg*)((uint32_t) _caps + _caps->capLeng);
        }
};

#endif