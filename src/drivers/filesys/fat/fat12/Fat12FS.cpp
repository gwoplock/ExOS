//
// Created by Garrett Battaglia on 1/16/18.
//

#include "Fat12FS.h"

Fat12File *Fat12FS::open(char *path, int flags, int mode)
{
	//TODO find file
	Fat12File *ret = new Fat12File(0);
	return ret;
}

//todo names, var sizes, structure taken from osdev wiki
bool Fat12FS::readCluster(uint16_t cluser, void* fileLoc, size_t fileLocSize){
	assert(fileLocSize >= (_FSInfo->secPerCluster * _FSInfo->bytePerSec));
	uint32_t fat_size = (_FSInfo->secCount != 0)? _FSInfo->secCount : _FSInfo->largeSecCount;
	uint32_t root_dir_sectors = ((_FSInfo->dirEntryCount * 32) + (_FSInfo->bytePerSec - 1)) / _FSInfo->bytePerSec;
	uint32_t first_data_sector = _FSInfo->resSec + (_FSInfo->FATs * fat_size) + root_dir_sectors;
	uint32_t first_sector_of_cluster = ((cluster - 2) * _FSInfo->secPerCluster) + first_data_sector;
	for (uint32_t i =0; i < _FSInfo->secPerCluster; i++){
		_device->read(first_sector_of_cluster);
		first_sector_of_cluster++;
	}
}