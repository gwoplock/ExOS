//
// Created by Garrett Battaglia on 1/16/18.
//

#include "Fat12FS.h"
#include "Fat12File.h"
#include "Fat12FSNode.h"

File *Fat12FS::open(char *path, int flags, int mode) {
	//TODO find file
	Fat12File *ret = new Fat12File(0);
	return ret;
}

//todo names, var sizes, structure taken from osdev wiki
bool Fat12FS::readCluster(uint16_t cluster, void* fileLoc, size_t fileLocSize) {
	assert(fileLocSize >= (_FSInfo->secPerCluster * _FSInfo->bytePerSec));
	uint32_t fat_size =
			(_FSInfo->secCount != 0) ?
					_FSInfo->secCount : _FSInfo->largeSecCount;
	uint32_t root_dir_sectors = ( (_FSInfo->dirEntryCount * 32)
			+ (_FSInfo->bytePerSec - 1)) / _FSInfo->bytePerSec;
	uint32_t first_data_sector = _FSInfo->resSec + (_FSInfo->FATs * fat_size)
			+ root_dir_sectors;
	uint32_t first_sector_of_cluster = ( (cluster - 2) * _FSInfo->secPerCluster)
			+ first_data_sector;
	for (uint32_t i = 0; i < _FSInfo->secPerCluster; i++) {
		//TODO after _device isnt void* uncommetn below
		//bool ret = _device->read(first_sector_of_cluster, fileLoc);
		//TODO return on read error
		first_sector_of_cluster++;
	}
}
//TODO check var sizes
void Fat12FS::buildDirStructure( ) {
	_root = new Fat12FSNode( );
	uint8_t* tempSector = (uint8_t*) malloc(_FSInfo->bytePerSec);
	uint8_t sectorOffset = 0;
	uint16_t startSector = (_FSInfo->resSec)
			+ (_FSInfo->FATs * _FSInfo->secPerFAT);
	uint16_t rootDirSize = (float) _FSInfo->dirEntryCount
			/ (float) _FSInfo->bytePerSec
			+ (_FSInfo->dirEntryCount % _FSInfo->bytePerSec != 0);
			//_device->read(startSector+i, tempCluster)
			//TODO there may be an issue if the size of a sector != a mult of the size of an entry... we will deal with that latter
	for (size_t i = 0; i < rootDirSize; i++) {
		if(tempSector[sectorOffset] == 0){
			break;
		}
		parseEntry(tempSector + sectorOffset);
		if (_tempLongName == nullptr){
			sectorOffset += sizeof(FatNormalFileName);
		} else {
			sectorOffset += sizeof(FatLongFileName);
		}
		if (sectorOffset >= _FSInfo->bytePerSec){
			//_device->read(startSectot+i, tempCluster)
		}
	}
}

void Fat12FS::parseEntry(uint8_t* sector){
	if(sector[0] == 0xE5){
		return;
	}
	if (sector[10] == 0x0F){
		//long file name
	} else {
		//normal file name
		if(false /*have long file name stored*/){
			//end of name, add name to entry we just read
		}
	}
}
