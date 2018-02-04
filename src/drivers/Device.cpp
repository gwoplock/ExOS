#include "Device.h"

class Device
{
  private:
    uint32_t _Id;

  public:
    Device():_Id(++lastDeviceId){

    }
}

Device *deviceList;

uint32_t lastDeviceId;