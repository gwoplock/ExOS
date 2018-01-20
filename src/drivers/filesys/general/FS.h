//
// Created by Garrett Battaglia on 1/20/18.
//

#ifndef EXOS_FS_H
#define EXOS_FS_H

#include "Global.h"
#include "FSNode.h"
#include "File.h"

class FS{
	private:
		FSNode _root;
	public:
		File* open(char *path, int flags, int mode);
};
#endif //EXOS_FS_H
