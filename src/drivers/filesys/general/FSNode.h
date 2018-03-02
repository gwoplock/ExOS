//
// Created by Garrett Battaglia on 1/20/18.
//

#ifndef EXOS_FSNODE_H
#define EXOS_FSNODE_H

#include "Global.h"

enum Type
{
	FILE,
	DIR,
	LINK
};

class FSNode
{
  private:
	char *_name;
	uint32_t _size;
	FSNode **_children;
	Type _type;
	size_t _childernCount;

  public:
	FSNode()
	{
		_name = "root";
		_size = 0;
		_type = DIR;
	}
	FSNode(char *name, uint32_t size, Type type)
	{
		_name = name;
		_size = size;
		_type = type;
		_children = nullptr;
		_childernCount = 0;
	}
	void add(FSNode *toAdd)
	{
		_children = (FSNode **)realloc(_children, sizeof(FSNode *) * (++_childernCount));
		_children[_childernCount - 1] = toAdd;
	}
	size_t childernCount()
	{
		return _childernCount;
	}
	FSNode **children()
	{
		return _children;
	}
	Type type()
	{
		return _type;
	}
	char *name()
	{
		return _name;
	}
	virtual uint32_t startSector() = 0;
	//Permissions permissons();
};

#endif //EXOS_FSNODE_H
