/*
 * Fat12FSNode.h
 *
 *  Created on: Jan 20, 2018
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_FILESYS_FAT_FAT12_FAT12FSNODE_H_
#define SRC_DRIVERS_FILESYS_FAT_FAT12_FAT12FSNODE_H_
#include "Global.h"
#include "Fat12FS.h"

//class Fat12FS;

class Fat12FSNode : public FSNode
{
  private:
	uint32_t _startCluster;
	Fat12FS *_host;

  public:
	Fat12FSNode(char *name, uint32_t size, Type type, uint32_t cluster, Fat12FS *fs) : FSNode(name, size, type), _startCluster(cluster), _host(fs)
	{
	}
	Fat12FSNode() : FSNode()
	{
	}
	//todo var names and size, taken from fat12fs.cpp
	virtual uint32_t startSector()
	{
		uint32_t fat_size = (_host->FSInfo()->secCount != 0) ? _host->FSInfo()->secCount : _host->FSInfo()->largeSecCount;
		uint32_t root_dir_sectors = ((_host->FSInfo()->dirEntryCount * 32) + (_host->FSInfo()->bytePerSec - 1)) / _host->FSInfo()->bytePerSec;
		uint32_t first_data_sector = _host->FSInfo()->resSec + (_host->FSInfo()->FATs * fat_size) + root_dir_sectors;
		return ((_startCluster - 2) * _host->FSInfo()->secPerCluster) + first_data_sector;
	}
	virtual ~Fat12FSNode()
	{
	}
	uint32_t startCluster()
	{
		return _startCluster;
	}
};

#endif /* SRC_DRIVERS_FILESYS_FAT_FAT12_FAT12FSNODE_H_ */
