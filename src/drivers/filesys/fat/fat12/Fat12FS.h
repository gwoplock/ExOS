//
// Created by Garrett Battaglia on 1/16/18.
//

#ifndef EXOS_FAT12_H
#define EXOS_FAT12_H

#include "drivers/filesys/fat/FatStructs.h"
#include "Global.h"
#include "drivers/filesys/general/FS.h"
#include "Fat12FSNode.h"

class Fat12File;

class Fat12FS : public FS{
	private:
		FatBPB* _FSInfo;
		char* _tempLongName = nullptr;
	public:
		File *open(char *path, int flags, int mode);

		FatBPB *FSInfo( ) {
			return _FSInfo;
		}
		bool readCluster(uint16_t cluser, void* fileLoc, size_t fileLocSize);
		void buildDirStructure();
		Fat12FSNode* parseEntry(uint8_t* sector);
		void buildTree(Fat12FSNode* root);
		Fat12FSNode* find(char* path, Fat12FSNode* root);
};

#endif //EXOS_FAT12_H
