#ifndef DEVICE_H_
#define DEVICE_H_

#include "Global.h"




extern uint32_t lastDeviceId;


class Device
{
	private:
	uint32_t _Id;

  	public:
		Device():_Id(++lastDeviceId){
		}
};

extern Device* deviceList;

#endif