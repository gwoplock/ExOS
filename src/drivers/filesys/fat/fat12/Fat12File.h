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
		Fat12File(size_t firstCluster){
			_lastCluster = firstCluster;
			void* _fileLoc = malloc((_device->FSInfo()->bytePerSec)*(_device->FSInfo()->secPerCluster));
			_device->readCluster(firstCluster, _fileLoc, (_device->FSInfo()->bytePerSec)*(_device->FSInfo()->secPerCluster));
		}
		size_t read(char* buffer, size_t size);

		bool readFromDisk();
};

#endif //EXOS_FAT12FILE_H
