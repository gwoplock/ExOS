//
// Created by Garrett Battaglia on 1/18/18.
//

#include "Assert.h"

extern "C" {
	/**
	 * @brief assert something is ture
	 * 
	 * @param expression: thing to check
	 */
	void assert(uint8_t expression) {
		if(!expression) {
			//TODO kernel panic...
		}
	}
}
