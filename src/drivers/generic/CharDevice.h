#ifndef CHARDEVICE_H_
#define CHARDEVICE_H_
#include "Global.h"
#include "device.h"

class CharDevice : public Device
{
  private:
  public:
  void read(char* readTo);
  char read();
};

#endif