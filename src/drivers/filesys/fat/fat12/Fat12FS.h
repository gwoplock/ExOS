//
// Created by Garrett Battaglia on 1/16/18.
//

#ifndef EXOS_FAT12_H
#define EXOS_FAT12_H

#include "Fat12File.h"
#include "drivers/filesys/fat/FatStructs.h"

class Fat12FS
{
	private:
		FatBPB _FSInfo;
	public:
		Fat12File *open(char *path, int flags, int mode);

		FatBPB *FSInfo()
		{
			return _FSInfo;
		}
};


#endif //EXOS_FAT12_H
