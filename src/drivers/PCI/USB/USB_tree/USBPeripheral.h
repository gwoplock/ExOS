#ifndef USB_PERIPHERAL_H_
#define USB_PERIPHERAL_H_

#include "Global.h"

class USBPeripheral
{
  protected:
    USBPeripheral **_ports;
    size_t _portCount;
    size_t _port;
    USBPeripheral *_left, *_right, *_parent;


  public:
    USBPeripheral(size_t port, size_t portCount, USBPeripheral* parent);
    void add(size_t port, USBPeripheral* toAdd);
    void remove(size_t port);
    size_t portCount(){
        return _portCount;
    }
    void left(USBPeripheral* sib){
      _left = sib;
    }
        void right(USBPeripheral* sib){
      _left = sib;
    }
};

#endif