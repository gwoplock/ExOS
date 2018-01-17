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
			if (readFromDisk()) {
				//error
			}
		}
	}
}

bool readFromDisk()
{
	
}