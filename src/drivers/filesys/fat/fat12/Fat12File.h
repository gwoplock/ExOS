//
// Created by Garrett Battaglia on 1/16/18.
//

#ifndef EXOS_FAT12FILE_H
#define EXOS_FAT12FILE_H

#include "drivers/filesys/File.h"
#include "Fat12FS.h"

class Fat12File: public File{
	private:
		size_t lastCluster;
		Fat12FS device;
	public:
		size_t read(char* buffer, size_t size);
};

#endif //EXOS_FAT12FILE_H
