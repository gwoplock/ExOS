//
// Created by Garrett Battaglia on 1/16/18.
//

#ifndef EXOS_FAT12_H
#define EXOS_FAT12_H

#include "Fat12File.h"

class Fat12FS{
	public:
		//TODO void* -> filedesc*
		File* open(char* path, int flags, int mode);

};


#endif //EXOS_FAT12_H
