//
// Created by Garrett Battaglia on 1/16/18.
//

#include "Fat12FS.h"
#include "Fat12File.h"
#include "Fat12FSNode.h"
#include "utils/string/Split.h"

File *Fat12FS::open(char *path, int flags, int mode) {
	Fat12FSNode* file = find(path,(Fat12FSNode*)_root );
	Fat12File *ret = new Fat12File(file->startCluster());
	return ret;
}

Fat12FSNode* Fat12FS::find(char* path, Fat12FSNode* root){
	char** split = strSplit(path, '/');
	if (split == nullptr){
		return root;
	}
	for (int i=0; i< root->childernCount(); i++){
		if (strcmp(root->children()[i]->name(), split[0]) == 0){
			return find(split[1], (Fat12FSNode*)root->children()[i]);
		}
	}
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
	//This conversion may not work correctly... oh well
	_root = new Fat12FSNode("Root", 0, DIR, ( (_FSInfo->resSec) + (_FSInfo->FATs * _FSInfo->secPerFAT) )/_FSInfo->secPerCluster);
	/*uint8_t* tempSector = (uint8_t*) malloc(_FSInfo->bytePerSec);
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
		Fat12FSNode* ret = parseEntry(tempSector + sectorOffset);
		if (_tempLongName == nullptr){
			sectorOffset += sizeof(FatNormalFileName);
		} else {
			sectorOffset += sizeof(FatLongFileName);
		}
		if(ret != nullptr){
			_root->add(ret);
			if(ret->type() == DIR){
				buildTree(ret);
			}
		}
		if (sectorOffset >= _FSInfo->bytePerSec){
			//_device->read(startSectot+i, tempCluster)
		}
	}*/
	buildTree((Fat12FSNode*)_root);
}

void Fat12FS::buildTree(Fat12FSNode* dir){
	uint8_t* tempSector = (uint8_t*) malloc(_FSInfo->bytePerSec);
	size_t offset = 0;
	while(tempSector[offset] != 0){
		Fat12FSNode* ret = parseEntry(tempSector + offset);
		if (_tempLongName == nullptr){
			offset += sizeof(FatNormalFileName);
		} else {
			offset += sizeof(FatLongFileName);
		}
		if(ret != nullptr){
			_root->add(ret);
			if(ret->type() == DIR){
				buildTree(ret);
			}
		}
		if (offset >= _FSInfo->bytePerSec){
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

Fat12FSNode* Fat12FS::parseEntry(uint8_t* sector){
	if(sector[0] == 0xE5){
		return nullptr;
	}
	if (sector[10] == 0x0F){
		//i belive this wont overrun and will end with a null in the right spot. also i hope this doesnt add a null somewhere
		FatLongFileName* entry = (FatLongFileName*)sector;
		uint32_t tempLeng = strlen(_tempLongName);
		_tempLongName = (char*) realloc(_tempLongName, tempLeng + 10+10+4);
		memcpy(_tempLongName+tempLeng, &entry->nameFirst, 10);
		memcpy(_tempLongName+tempLeng +10, &entry->nameMid, 10);
		memcpy(_tempLongName+tempLeng+10+10, &entry->nameEnd, 4);
		_tempLongName[tempLeng+10+10+4+1] = '\0';
		return nullptr;
	} else {
		FatNormalFileName* entry = (FatNormalFileName*) sector;
		Type type = (entry->attribute && 0x10) != 0 ? DIR : FILE;
		char* name  = nullptr;
		if(false /*have long file name stored*/){
			name = (char*) malloc(strlen(_tempLongName) * sizeof(uint16_t));
			memcpy(name, _tempLongName, strlen(_tempLongName)*2);
		} else {
			name = (char*) malloc(strlen((char*)entry->name) * sizeof(uint8_t));
			memcpy(name, entry->name, strlen((char*)entry->name));
		}
		uint32_t size =  entry->size;
		uint32_t cluster = entry->lowClusterNumber;
		return new Fat12FSNode(name, size, type, cluster);
		
	}
}
