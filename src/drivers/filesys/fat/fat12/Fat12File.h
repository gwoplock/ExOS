//
// Created by Garrett Battaglia on 1/16/18.
//

#ifndef EXOS_FAT12FILE_H
#define EXOS_FAT12FILE_H

#include "drivers/filesys/general/File.h"
#include "Fat12FS.h"
#include "Global.h"

//class Fat12FS;

/**
 * @brief a file in the fat 12 FS
 * @see class File
 */
class Fat12File: public File{
	private:
	/**
	 * @brief the last cluster read from disk 
	 * 
	 */
		size_t _lastCluster;
		/**
		 * @brief the device with the file system
		 * 
		 */
		Fat12FS* _device;
		/**
		 * @brief how far into the buffer read
		 * 
		 */
		uint32_t _lastByteRead;
		/**
		 * @brief how far into the file loaded
		 * 
		 */
		uint32_t _lastByteLoaded;
		/**
		 * @brief location of the buffer for reading off the disk
		 * 
		 */
		void* _fileLoc;
		/**
		 * @brief how big the buffer for off the disk is
		 * @see _fileLoc
		 * 
		 */
		size_t _fileLocSize;
		/**
		 * @brief unkown
		 * 
		 */
		//TODO what is this for
		uint32_t _fileLocStartInFile;
	public:
		/**
		 * @brief Construct a new Fat 12 File object
		 * 
		 * @param firstCluster the cluster to start with
	 	*/
		Fat12File(size_t firstCluster){
			_lastCluster = firstCluster;
			void* _fileLoc = malloc((_device->FSInfo()->bytePerSec)*(_device->FSInfo()->secPerCluster));
			_device->readCluster(firstCluster, _fileLoc, (_device->FSInfo()->bytePerSec)*(_device->FSInfo()->secPerCluster));
		}
		/**
 		* @brief read bytes into buffer
		* 
		* @param buffer what to read into
		* @param size how many to read
		* @return size_t how many actually read
 		*/
		size_t read(char* buffer, size_t size);
		/**
 		* @brief read clusters from disk into buffer
 		* @note will try to fill the buffer
 		* @return true able to read
 		* @return false unable to read
 		*/
		bool readFromDisk();
};

#endif //EXOS_FAT12FILE_H
