//
// Created by Garrett Battaglia on 1/16/18.
//

#include "Fat12FS.h"
#include "Fat12File.h"
#include "Fat12FSNode.h"
#include "utils/string/Split.h"
/**
 * @brief open a file
 * 
 * @param path path to open
 * @param flags not currently used
 * @param mode not currently used
 * @return File* opened file, is a Fat12File
 */
File *Fat12FS::open(char *path, int flags, int mode)
{
	(void)flags;
	(void)mode;
	Fat12FSNode *file = find(path, (Fat12FSNode *)_root);
	Fat12File *ret = new Fat12File(file->startCluster());
	return ret;
}
/**
 * @brief find a file from path
 * 
 * @param path file to find
 * @param root starting point
 * @return Fat12FSNode* the file at path, null if not found
 */
Fat12FSNode *Fat12FS::find(char *path, Fat12FSNode *root)
{
	char **split = strSplit(path, '/');
	if (split == nullptr)
	{
		return root;
	}
	for (unsigned int i = 0; i < root->childernCount(); i++)
	{
		if (strcmp(root->children()[i]->name(), split[0]) == 0)
		{
			return find(split[1], (Fat12FSNode *)root->children()[i]);
		}
	}
	return nullptr;
}
/**
 * @brief read a cluster from disk
 * 
 * @param cluster cluster to read
 * @param fileLoc where to read to
 * @param fileLocSize how much to read
 * @return true 
 * @return false 
 */
//todo names, var sizes, structure taken from osdev wiki
bool Fat12FS::readCluster(uint16_t cluster, void *fileLoc, size_t fileLocSize)
{
	(void)fileLoc;
	assert(fileLocSize >= (_FSInfo->secPerCluster * _FSInfo->bytePerSec));
	uint32_t fat_size =
		(_FSInfo->secCount != 0) ? _FSInfo->secCount : _FSInfo->largeSecCount;
	uint32_t root_dir_sectors = ((_FSInfo->dirEntryCount * 32) + (_FSInfo->bytePerSec - 1)) / _FSInfo->bytePerSec;
	uint32_t first_data_sector = _FSInfo->resSec + (_FSInfo->FATs * fat_size) + root_dir_sectors;
	uint32_t first_sector_of_cluster = ((cluster - 2) * _FSInfo->secPerCluster) + first_data_sector;
	for (uint32_t i = 0; i < _FSInfo->secPerCluster; i++)
	{
		//TODO after _device isnt void* uncommetn below
		//bool ret = _device->read(first_sector_of_cluster, fileLoc);
		//TODO return on read error
		first_sector_of_cluster++;
	}
	return true;
}

/**
 * @brief build the directory structure into a DAG
 * 
 */
//TODO check var sizes
void Fat12FS::buildDirStructure()
{
	//This conversion may not work correctly... oh well
	_root = new Fat12FSNode("Root", 0, DIR, ((_FSInfo->resSec) + (_FSInfo->FATs * _FSInfo->secPerFAT)) / _FSInfo->secPerCluster, this);
	buildTree((Fat12FSNode *)_root);
}
/**
 * @brief build a dir structure starting at dir
 * 
 * @param dir where to start
 */
void Fat12FS::buildTree(Fat12FSNode *dir)
{
	(void)dir;
	uint8_t *tempSector = (uint8_t *)malloc(_FSInfo->bytePerSec);
	size_t offset = 0;
	//_device.read(...)
	while (tempSector[offset] != 0)
	{
		Fat12FSNode *ret = parseEntry(tempSector + offset);
		if (_tempLongName == nullptr)
		{
			offset += sizeof(FatNormalFileName);
		}
		else
		{
			offset += sizeof(FatLongFileName);
		}
		if (ret != nullptr)
		{
			_root->add(ret);
			if (ret->type() == DIR)
			{
				buildTree(ret);
			}
		}
		if (offset >= _FSInfo->bytePerSec)
		{
			//_device->read(startSectot+i, tempCluster)
		}
	}
	/*for (size_t i =0; i<dir->childernCount() ; i++){
		if(root->children()[i]->type() == DIR){
			//TODO add
		}
	}*/
	free(tempSector);
}

/**
 * @brief parse an etry in the FAT
 * 
 * @param sector sector to chech
 * @return Fat12FSNode* node in graph 
 * @see Fat12FS::buildTree
 */
Fat12FSNode *Fat12FS::parseEntry(uint8_t *sector)
{
	if (sector[0] == 0xE5)
	{
		return nullptr;
	}
	if (sector[10] == 0x0F)
	{
		//i belive this wont overrun and will end with a null in the right spot. also i hope this doesnt add a null somewhere
		FatLongFileName *entry = (FatLongFileName *)sector;
		uint32_t tempLeng = strlen(_tempLongName);
		_tempLongName = (char *)realloc(_tempLongName, tempLeng + 10 + 10 + 4);
		memcpy(_tempLongName + tempLeng, &entry->nameFirst, 10);
		memcpy(_tempLongName + tempLeng + 10, &entry->nameMid, 10);
		memcpy(_tempLongName + tempLeng + 10 + 10, &entry->nameEnd, 4);
		_tempLongName[tempLeng + 10 + 10 + 4 + 1] = '\0';
		return nullptr;
	}
	else
	{
		FatNormalFileName *entry = (FatNormalFileName *)sector;
		Type type = (entry->attribute && 0x10) != 0 ? DIR : FILE;
		char *name = nullptr;
		if (false /*have long file name stored*/)
		{
			name = (char *)malloc(strlen(_tempLongName) * sizeof(uint16_t));
			memcpy(name, _tempLongName, strlen(_tempLongName) * 2);
		}
		else
		{
			name = (char *)malloc(strlen((char *)entry->name) * sizeof(uint8_t));
			memcpy(name, entry->name, strlen((char *)entry->name));
		}
		uint32_t size = entry->size;
		uint32_t cluster = entry->lowClusterNumber;
		return new Fat12FSNode(name, size, type, cluster, this);
	}
}
