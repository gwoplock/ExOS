/*
 * HostController.h
 *
 *  Created on: Aug 31, 2017
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_PCI_USB_HOSTCONTROLLER_HOSTCONTROLLER_H_
#define SRC_DRIVERS_PCI_USB_HOSTCONTROLLER_HOSTCONTROLLER_H_

#include "Global.h"
#include "drivers/PCI/USB/USBEvent.h"
class HostController {
	protected:
		void* _BAR0;
		void* _BAR1;
		void* _BAR2;
		void* _BAR3;
		void* _BAR4;
	public:
		HostController( );
		HostController(void** baseAddresses) {
			_BAR0 = baseAddresses[0];
			_BAR1 = baseAddresses[1];
			_BAR2 = baseAddresses[2];
			_BAR3 = baseAddresses[3];
			_BAR4 = baseAddresses[4];
		}
		HostController(void* BAR0, void* BAR1 = nullptr, void* BAR2 = nullptr,
				void* BAR3 = nullptr, void* BAR4 = nullptr) {
			_BAR0 = BAR0;
			_BAR1 = BAR1;
			_BAR2 = BAR2;
			_BAR3 = BAR3;
			_BAR4 = BAR4;
		}
		virtual ~HostController( );
		USBEvent* poll();
};

#endif /* SRC_DRIVERS_PCI_USB_HOSTCONTROLLER_HOSTCONTROLLER_H_ */
