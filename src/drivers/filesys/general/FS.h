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
	/**
	 * @brief root node in tree
	 * 
	 */
		FSNode* _root;
		/**
		 * @brief device file system is on
		 * 
		 */
		void* _device;
	public:
		/**
		* @brief open a file
		* 
		* @param path path to file
		* @param flags open flags
		* @param mode how to open
		* @return File* file object for file
		*/
		virtual File* open(char *path, int flags, int mode) = 0;
		/**
		 * @brief build the directory structure
		 * 
		 */
		virtual void buildDirStructure() = 0;
};
#endif //EXOS_FS_H
