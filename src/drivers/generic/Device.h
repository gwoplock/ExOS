#include "Global.h"




uint32_t lastDeviceId;


class Device
{
  private:
    uint32_t _Id;

  public:
    Device():_Id(++lastDeviceId){

    }
};

Device* deviceList = nullptr;