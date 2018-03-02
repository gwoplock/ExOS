//
// Created by Garrett Battaglia on 1/20/18.
//

#ifndef EXOS_FS_H
#define EXOS_FS_H

#include "Global.h"
#include "FSNode.h"
#include "File.h"

class FS{
	protected:
		FSNode* _root;
		void* _device;
	public:
		virtual File* open(char *path, int flags, int mode) = 0;
		virtual void buildDirStructure() = 0;
};
#endif //EXOS_FS_H
