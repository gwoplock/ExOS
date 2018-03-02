//
// Created by Garrett Battaglia on 1/18/18.
//

#include "Assert.h"

extern "C" {
	void assert(uint8_t expression) {
		if(!expression) {
			//TODO kernel panic...
		}
	}
};
