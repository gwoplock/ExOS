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

    _ports[port] = toAdd;

    if (_portCount== 1){
        toAdd->left(nullptr);
        toAdd->right(nullptr);
    } 
    if (port == 0){
        toAdd->left(nullptr);
        for (int i = port; i < _portCount; i++){
            if (_ports[i] != nullptr){
                toAdd->right(_ports[i]);
                break;
            }
        }
    } else if (_portCount -1 == port){
        for (int i = port; i > 0; i--){
            if (_ports[i] != nullptr){
                toAdd->left(_ports[i]);
                break;
            }
        }
        toAdd->right(nullptr);
    } else {
        for (int i = port; i > 0; i--){
            if (_ports[i] != nullptr){
                toAdd->left(_ports[i]);
                break;
            }
        }
        for (int i = port; i < _portCount; i++){
            if (_ports[i] != nullptr){
                toAdd->right(_ports[i]);
                break;
            }
        }
    }

}

 void USBPeripheral::remove(size_t port){
     assert(_ports[port] != nullptr);
     _ports[port]->_right->_left = _ports[port]->_left;
      _ports[port]->_left->_right = _ports[port]->_right;
      _ports[port] = nullptr;
 }