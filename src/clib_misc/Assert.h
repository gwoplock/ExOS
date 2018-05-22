//
// Created by Garrett Battaglia on 1/18/18.
//

#ifndef EXOS_ASSERT_H
#define EXOS_ASSERT_H

#include "Global.h"

extern "C"{
    /**
	 * @brief assert something is ture
	 * 
	 * @param expression: thing to check
	 */
void assert(uint8_t expression);
};


#endif //EXOS_ASSERT_H
