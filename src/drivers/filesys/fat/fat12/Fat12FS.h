//
// Created by Garrett Battaglia on 1/16/18.
//

#ifndef EXOS_FAT12_H
#define EXOS_FAT12_H

#include "Fat12File.h"
#include "drivers/filesys/fat/FatStructs.h"

class Fat12File;

class Fat12FS : public FS{
	private:
		FatBPB* _FSInfo;
		//TODO replace with device.
		void* _device;
	public:
		Fat12File *open(char *path, int flags, int mode);

		FatBPB *FSInfo( ) {
			return _FSInfo;
		}
		bool readCluster(uint16_t cluser, void* fileLoc, size_t fileLocSize);
};

#endif //EXOS_FAT12_H
