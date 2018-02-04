#include "Global.h"
#include "Device.h"

class BlockDevice :public Device{
private:
public:
virtual void read(uint32_t sector, void* readTo) = 0;
};