/*
 * Fat12FSNode.h
 *
 *  Created on: Jan 20, 2018
 *      Author: garrett
 */

#ifndef SRC_DRIVERS_FILESYS_FAT_FAT12_FAT12FSNODE_H_
#define SRC_DRIVERS_FILESYS_FAT_FAT12_FAT12FSNODE_H_
#include "Global.h"

class Fat12FSNode: public FSNode {
	private:
		uint32_t _startCluster;
	public:
		Fat12FSNode(char* name, uint32_t size, Type type, uint32_t cluster):FSNode(name,size,type), _startCluster(cluster){

		}
		Fat12FSNode():FSNode(){
			
		}
		virtual uint32_t startSector(){

		}
		virtual ~Fat12FSNode( ){

		}
		uint32_t startCluster(){
			return _startCluster;
		}
};

#endif /* SRC_DRIVERS_FILESYS_FAT_FAT12_FAT12FSNODE_H_ */
