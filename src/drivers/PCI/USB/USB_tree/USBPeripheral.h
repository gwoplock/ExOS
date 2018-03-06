#ifndef USB_PERIPHERAL_H_
#define USB_PERIPHERAL_H_

#include "Global.h"

class USBPeripheral
{
  private:
    USBPeripheral **_ports;
    size_t _portCount;
    size_t _port;

  public:
    USBPeripheral(size_t port, size_t portCount)
    {
        _port = port;
        _portCount = portCount;
        _ports = (USBPeripheral**) malloc(sizeof(USBPeripheral *) * portCount);
            memSet((void*)_ports, (sizeof(USBPeripheral*) * portCount), 0);
    }
    void add(size_t port, USBPeripheral* toAdd)
    {
        assert(_ports[port] == nullptr);
        _ports[port] = toAdd;
    }
};

#endif