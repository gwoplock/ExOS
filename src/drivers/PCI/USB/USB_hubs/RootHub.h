#ifndef ROOT_HUB_H_
#define ROOT_HUB_H_

#include "Global.h"
#include "USBHubAbstract.h"

class USBRootHub: public USBHubAbstract{
    public:
        USBRootHub():USBHubAbstract(){

        }   
        USBRootHub(USBHostController* host): USBHubAbstract(host){
            
        }
};

#endif