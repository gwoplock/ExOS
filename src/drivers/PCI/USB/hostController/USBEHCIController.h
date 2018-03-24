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

struct USBCmd {
    uint8_t runStop:1;
    uint8_t reset:1;
    uint8_t frameSizeList:2;
    uint8_t periodSchedEnable:1;
    uint8_t asyncSchedEnable:1;
    uint8_t intOnAsyncDoorbell:1;
    uint8_t lightReset:1;
    uint8_t asyncSchedParkModeCount:2;
    uint8_t reserved1:1;
    uint8_t asyncSchedParkModeEnable:1;
    uint8_t reserved2:4;
    uint8_t interruptThreshCont;
    uint8_t reserved3;
};

struct USBStat {
    uint8_t rxInt:1;
    uint8_t errInt:1;
    uint8_t portChange:1;
    uint8_t frameListRollover:1;
    uint8_t systemError:1;
    uint8_t asyncDoorbell:1;
    uint8_t reserved1:6;
    uint8_t hcHalted:1;
    uint8_t reclamation:1;
    uint8_t periodiCSchedStat:1;
    uint8_t asyncSchedStat:1;
    uint16_t reserved2;
};
struct IntEnable{
    uint8_t usbIntEnable:1;
    uint8_t ErrIntEnable:1;
    uint8_t portChangeIntEnable:1;
    uint8_t frameListRollIntEnable:1;
    uint8_t hostSystemIntEnable:1;
    uint8_t intOnAsyncAdvanceEnable:1;
    uint8_t reserved1:2;
    uint16_t reserved2;
    uint8_t reserved3;
};
struct FrameIndex{
    uint16_t frameIndex:13;
    uint8_t reserved1:3;
    uint16_t reserved2;
};
struct FrameListBase{
    uint16_t reserved:12;
    uint32_t baseAddr:20;
};

struct AsyncListAddr{
    uint8_t reserved:5;
    uint32_t linkPointerLow:28;
};

struct ConfigFlags{
    uint8_t configFlag:1;
    uint32_t reserved:31;
};

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

struct operReg{
    USBCmd cmd;
    USBStat stat;
    IntEnable intEnable;
    FrameIndex frameIndex;
    uint32_t  CDSeg;
    FrameListBase frameListBase;
    AsyncListAddr asyncListAddr;
    uint8_t reserved[35];
    ConfigFlags flags;
    EHCIPortStatCont ports;
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