//
// Created by Garrett Battaglia on 1/20/18.
//

#ifndef EXOS_FSNODE_H
#define EXOS_FSNODE_H

#include "Global.h"

enum Type{
	FILE, DIR, LINK
};

class FSNode{
	private:
		char* _name;
		uint32_t _size;
		FSNode** _children;
		Type _type;
		size_t _childernCount;
	public:
		FSNode(){
			_name="root";
			_size =0;
			_type=DIR;
		}
		FSNode(char* name, uint32_t size, Type type){
			_name=name;
			_size = size;
			_type =type;
			_children = nullptr;
			_childernCount = 0;
		}
		virtual uint32_t startSector() = 0;
		//Permissions permissons();
};

#endif //EXOS_FSNODE_H
