//
// Created by Garrett Battaglia on 1/16/18.
//

#ifndef EXOS_FATSTRUCTS_H
#define EXOS_FATSTRUCTS_H

#include "Global.h"

struct FatTime{
	uint8_t hour:5;
	uint8_t min:6;
	uint8_t second:5;
};

struct FatDay{
	uint8_t year:7;
	uint8_t month:4;
	uint8_t day:5;
};

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

struct FatNormalFileName {
	uint8_t name[11];
	uint8_t attribute;
	uint8_t reserved;
	uint8_t creationTimeMS;
	FatTime createTime;
	FatDay createDay;
	FatDay latsAccessedDay;
	uint16_t highClusterNumber;
	FatTime modTime;
	FatDay modDay;
	uint16_t lowClusterNumber;
	uint32_t size;
};

struct FatLongFileName {

};

#endif //EXOS_FATSTRUCTS_H
