//
// Created by Garrett Battaglia on 1/16/18.
//

#include "Fat12File.h"
#include "memory/Mem.h"
/**
 * @brief read bytes into buffer
 * 
 * @param buffer what to read into
 * @param size how many to read
 * @return size_t how many actually read
 */
size_t Fat12File::read(char *buffer, size_t size)
{
	size_t bytesRead = 0;
	while (bytesRead < size)
	{
		if (size < (_fileLocSize - _lastByteRead))
		{
			memcpy(buffer + bytesRead,
				   (uint8_t *)_fileLoc + (_lastByteRead - 
				   _fileLocStartInFile), size);
			bytesRead += size;
		}
		else
		{
			memcpy(buffer + bytesRead,
				   (uint8_t *)_fileLoc + (_lastByteRead - 
				   _fileLocStartInFile), _lastByteLoaded - _lastByteRead);
			bytesRead += _lastByteLoaded - _lastByteRead;
			if (!readFromDisk())
			{
				return bytesRead;
			}
		}
	}
	return 0;
}

/**
 * @brief read clusters from disk into buffer
 * @note will try to fill the buffer
 * @return true able to read
 * @return false unable to read
 */
//TODO naming and types and general structure, taken from osdev wiki
bool Fat12File::readFromDisk()
{
	unsigned char FAT_table[_device->FSInfo()->bytePerSec];
	uint32_t read = 0;
	while (read < _fileLocSize && _fileLocSize - read >= 
	      (_device->FSInfo()->secPerCluster * _device->FSInfo()->bytePerSec))
	{
		unsigned int fat_offset = _lastCluster + (_lastCluster / 2);
		unsigned int ent_offset = fat_offset % _device->FSInfo()->bytePerSec;
		unsigned short table_value = *(unsigned short *)&FAT_table[ent_offset];

		if (_lastCluster & 0x0001)
			table_value = table_value >> 4;
		else
			table_value = table_value & 0x0FFF;
		if (table_value >= 0xFF8)
		{
			//TODO make sure this frees everything
			free((uint8_t *)_fileLoc + read);
			_fileLocSize = read;
			return true;
		}
		else
		{
			bool ret = _device->readCluster(table_value, 
					            (uint8_t *)_fileLoc + read,
								_fileLocSize - read);
			if (!ret)
			{
				return false;
			}
			read += (_device->FSInfo()->secPerCluster * _device->FSInfo()->bytePerSec);
			_lastCluster = table_value;
		}
	}
	_lastByteLoaded += read;
	return true;
}
