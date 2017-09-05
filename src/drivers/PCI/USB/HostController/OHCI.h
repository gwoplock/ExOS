/*
 * OHCI.h
 *
 *  Created on: Aug 31, 2017
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_PCI_USB_HOSTCONTROLLER_OHCI_H_
#define SRC_DRIVERS_PCI_USB_HOSTCONTROLLER_OHCI_H_

#include "../../../../global.h"
#include "HostController.h"

class OHCI: public HostController {
	public:
		OHCI( );
		OHCI(void* BAR0) :
				HostController(BAR0) {

		}
		virtual ~OHCI( );
		uint32_t revision( ) {
			return * ((uint32_t*) _BAR0);
		}
		uint32_t commandStatus( ) {
			return * ((uint32_t*) _BAR0 + 1);
		}
		uint32_t interruptStatus( ) {
			return * ((uint32_t*) _BAR0 +2 );
		}
		uint32_t interruptEnable( ) {
			return * ((uint32_t*) _BAR0+3);
		}
		uint32_t interruptDisable( ) {
			return * ((uint32_t*) _BAR0+4);
		}
		uint32_t HCCA( ) {
			return * ((uint32_t*) _BAR0+5);
		}
		uint32_t periodCurrent( ) {
			return * ((uint32_t*) _BAR0+6);
		}
		uint32_t controlHead( ) {
			return * ((uint32_t*) _BAR0+7);
		}
		uint32_t controlCurrent( ) {
			return * ((uint32_t*) _BAR0+8);
		}
		uint32_t bulkHead( ) {
			return * ((uint32_t*) _BAR0+9);
		}
		uint32_t bulkCurrent( ) {
			return * ((uint32_t*) _BAR0+10);
		}
		uint32_t doneHead( ) {
			return * ((uint32_t*) _BAR0+11);
		}
		uint32_t fmInterval( ) {
			return * ((uint32_t*) _BAR0+12);
		}
		uint32_t fmRemaining( ) {
			return * ((uint32_t*) _BAR0+13);

		}
		uint32_t fmNumber( ) {
			return * ((uint32_t*) _BAR0+14);
		}
		uint32_t periodicStart( ) {
			return * ((uint32_t*) _BAR0+15);
		}
		uint32_t lsThreshold( ) {
			return * ((uint32_t*) _BAR0+16);
		}
		uint32_t rhDescriptorA( ) {
			return * ((uint32_t*) _BAR0+17);

		}
		uint32_t rhDescriptorB( ) {
			return * ((uint32_t*) _BAR0+18);
		}
		uint32_t rhStatus( ) {
			return * ((uint32_t*) _BAR0+19);
		}
};

#endif /* SRC_DRIVERS_PCI_USB_HOSTCONTROLLER_OHCI_H_ */
