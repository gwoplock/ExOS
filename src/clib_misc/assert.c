//
// Created by Garrett Battaglia on 1/18/18.
//

#include "assert.h"

extern "c"{
void assert(uint8_t expression){
	if(!expression){
		//TODO kernel panic...
	}
}
};