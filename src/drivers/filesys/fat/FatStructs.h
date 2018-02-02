//
// Created by Garrett Battaglia on 1/16/18.
//

#ifndef EXOS_FATSTRUCTS_H
#define EXOS_FATSTRUCTS_H

#include "Global.h"

struct FatBPB{
	uint8_t jmp[3];
	uint8_t oemIdent[8];
	uint16_t bytePerSec;
	uint8_t secPerCluster;
	uint16_t resSec;
	uint8_t FATs;
	uint16_t dirEntryCount;
	uint16_t secCount;
	uint8_t mediaType;
	uint16_t secPerFAT;
	uint16_t secPerTrack;
	uint16_t heads;
	uint32_t hiddenSec;
	uint32_t largeSecCount;
};

#endif //EXOS_FATSTRUCTS_H
