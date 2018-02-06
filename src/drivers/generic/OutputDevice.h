#ifndef OUTPUT_DEVICE_H_
#define OUTPUT_DEVICE_H_

#include "Device.h"

class OutputDevice : public Device
{
  private:
  public:
  void write(char* toWrite, size_t size);
};

#endif