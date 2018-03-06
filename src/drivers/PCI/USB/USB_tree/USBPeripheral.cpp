#include "USBPeripheral.h"

USBPeripheral::USBPeripheral(size_t port, size_t portCount, USBPeripheral* parent){
    _port = port;
    _portCount = portCount;
    _ports = (USBPeripheral**) malloc(sizeof(USBPeripheral*)*portCount);
    memSet((void*)_ports, (sizeof(USBPeripheral*) * portCount), 0);
    _parent = parent;
    if (parent != nullptr){
        parent->add(port, this);
    }
}
void USBPeripheral::add(size_t port, USBPeripheral* toAdd){
    //TODO not done
    if (_portCount== 1){
        toAdd->left(nullptr);
        toAdd->right(nullptr);
    } 
    if (port == 0){
        toAdd->left(nullptr);
        //TODo right
    } else if (_portCount -1 == port){
        //TODO left
        toAdd->right(nullptr);
    } else {
        //TODO both
    }

}