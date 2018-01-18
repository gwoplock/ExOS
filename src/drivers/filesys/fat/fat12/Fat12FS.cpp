//
// Created by Garrett Battaglia on 1/16/18.
//

#include "Fat12FS.h"

Fat12File *Fat12FS::open(char *path, int flags, int mode)
{
	Fat12File *ret = new Fat12File();
	return ret;
}

bool Fat12FS::readCluster(uint16_t cluser, void* fileLoc, size_t fileLocSize){
	assert(fileLocSize >= (_FSInfo->secPerCluster * _FSInfo->bytePerSec));
	//TODO read from disk
}