/*
 * OHCI.h
 *
 *  Created on: Aug 31, 2017
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_PCI_USB_HOSTCONTROLLER_OHCI_H_
#define SRC_DRIVERS_PCI_USB_HOSTCONTROLLER_OHCI_H_

#include "HostController.h"

class OHCI: public HostController {
	public:
		OHCI( );
		virtual ~OHCI( );
};

#endif /* SRC_DRIVERS_PCI_USB_HOSTCONTROLLER_OHCI_H_ */
