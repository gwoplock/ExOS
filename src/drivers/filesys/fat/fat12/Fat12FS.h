//
// Created by Garrett Battaglia on 1/16/18.
//

#ifndef EXOS_FAT12_H
#define EXOS_FAT12_H

#include "drivers/filesys/fat/FatStructs.h"
#include "Global.h"
#include "drivers/filesys/general/FS.h"
//#include "Fat12FSNode.h"

class Fat12File;
class Fat12FSNode;
/**
 * @brief class storing info about fat 12 file system
 * 
 */
class Fat12FS : public FS
{
	private:
		FatBPB *_FSInfo;
		char *_tempLongName = nullptr;
	public:
		/**
		* @brief open a file
		* 
		* @param path path to open
		* @param flags not currently used
		* @param mode not currently used
		* @return File* opened file, is a Fat12File
		*/
		File *open(char *path, int flags, int mode);
		/**
		* @brief get the file system info from the BPB
		* 
		* @return FatBPB* the fs info
		*/
		FatBPB *FSInfo() {
			return _FSInfo;
		}

		/**
		* @brief read a cluster from disk
		* 
		* @param cluster cluster to read
		* @param fileLoc where to read to
		* @param fileLocSize how much to read
		* @return true 
		* @return false 
		*/
		bool readCluster(uint16_t cluser, void *fileLoc, size_t fileLocSize);
		/**
		* @brief build the directory structure into a DAG
		* 
		*/
		void buildDirStructure();
		/**
		* @brief parse an etry in the FAT
		* 
		* @param sector sector to chech
		* @return Fat12FSNode* node in graph 
		* @see Fat12FS::buildTree
		*/
		Fat12FSNode *parseEntry(uint8_t *sector);
		/**
		* @brief build a dir structure starting at dir
		* 
		* @param dir where to start
		*/
		void buildTree(Fat12FSNode *root);
		/**
		* @brief find a file from path
		* 
		* @param path file to find
		* @param root starting point
		* @return Fat12FSNode* the file at path, null if not found
		*/
		Fat12FSNode *find(char *path, Fat12FSNode *root);
};

#endif //EXOS_FAT12_H
