//
// Created by Garrett Battaglia on 1/16/18.
//

#include "Fat12File.h"

size_t Fat12File::read(char *buffer, size_t size)
{
	size_t bytesRead = 0;
	while (bytesRead < size) {
		if (size < (_fileLocSize - _lastByteRead)) {
			memcpy(buffer + bytesRead, _fileLoc + (_lastByteRead - _fileLocStartInFile), size);
			bytesRead += size;
		} else {
			memcpy(buffer + bytesRead, _fileLoc + (_lastByteRead - _fileLocStartInFile),
			       _lastByteLoaded - _lastByteRead);
			bytesRead += _lastByteLoaded - _lastByteRead;
			if (!readFromDisk()) {
				return bytesRead;
			}
		}
	}
}

//TODO naming and types and general structure, taken from osdev wiki
bool readFromDisk()
{
	uint16_t firstFatSec = _device.FSInfo()->resSec;
	unsigned char FAT_table[_device.FSInfo()->bytePerSec];
	unsigned int fat_offset = active_cluster + (active_cluster / 2);// multiply by 1.5
	unsigned int fat_sector = first_fat_sector + (fat_offset / bytePerSec);
	unsigned int ent_offset = fat_offset % bytePerSec;

	unsigned short table_value = *(unsigned short*)&FAT_table[ent_offset];

	if(active_cluster & 0x0001)
		table_value = table_value >> 4;
	else
		table_value = table_value & 0x0FFF;
	if (table_value >=  0xFF8){
		return false;
	} else {
		bool ret =_device.readCluster(table_value, _fileLoc, _fileLocSize);
	}
}