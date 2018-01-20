//
// Created by Garrett Battaglia on 1/16/18.
//

#ifndef EXOS_FAT12FILE_H
#define EXOS_FAT12FILE_H

#include "drivers/filesys/File.h"
#include "Fat12FS.h"

class Fat12FS;

class Fat12File: public File{
	private:
		size_t _lastCluster;
		Fat12FS* _device;
		uint32_t _lastByteRead;
		uint32_t _lastByteLoaded;
		void* _fileLoc;
		size_t _fileLocSize;
		//TODO what is this for
		uint32_t _fileLocStartInFile;
	public:
		size_t read(char* buffer, size_t size);

		bool readFromDisk();
};

#endif //EXOS_FAT12FILE_H
