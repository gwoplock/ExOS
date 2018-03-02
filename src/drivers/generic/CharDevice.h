#ifndef CHARDEVICE_H_
#define CHARDEVICE_H_
#include "Global.h"
#include "Device.h"

class CharDevice : public Device
{
  private:
  public:
  virtual void read(char* readTo) =0 ;
  virtual char read()=0;
};

#endif
