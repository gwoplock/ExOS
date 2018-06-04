//
// Created by Garrett Battaglia on 1/20/18.
//

#ifndef EXOS_FSNODE_H
#define EXOS_FSNODE_H

#include "Global.h"

/**
 * @brief type of node
 * 
 */
enum Type
{
	FILE,
	DIR,
	LINK
};

class FSNode
{
  private:
	/**
	 * @brief name of file reped by node
	 * 
	 */
	char *_name;
	/**
	 * @brief size of the file
	 * @note 0 if not a file
	 */
	uint32_t _size;
	/**
	 * @brief children nodes
	 * 
	 */
	FSNode **_children;
	/**
	 * @brief type of node
	 * 
	 */
	Type _type;
	/**
	 * @brief how many children the node has
	 * 
	 */
	size_t _childernCount;

  public:
  /**
   * @brief Construct a new FSNode object
   * 
   */
	FSNode()
	{
		_name = "root";
		_size = 0;
		_type = DIR;
	}
	/**
	 * @brief Construct a new FSNode object
	 * 
	 * @param name name of file
	 * @param size size of file
	 * @param type type of file
	 */
	FSNode(char *name, uint32_t size, Type type)
	{
		_name = name;
		_size = size;
		_type = type;
		_children = nullptr;
		_childernCount = 0;
	}
	/**
	 * @brief add a child
	 * 
	 * @param toAdd child to add
	 */
	void add(FSNode *toAdd)
	{
		_children = (FSNode **)realloc(_children, sizeof(FSNode *) * (++_childernCount));
		_children[_childernCount - 1] = toAdd;
	}
	/**
	 * @brief get the num of children
	 * 
	 * @return size_t num of children
	 */
	size_t childernCount()
	{
		return _childernCount;
	}
	/**
	 * @brief get the children array
	 * 
	 * @return FSNode** children
	 */
	FSNode **children()
	{
		return _children;
	}
	/**
	 * @brief get type of file
	 * 
	 * @return Type type of file
	 */
	Type type()
	{
		return _type;
	}
	/**
	 * @brief get name of file
	 * 
	 * @return char* name
	 */
	char *name()
	{
		return _name;
	}
	/**
	 * @brief get where the file starts on disk
	 * 
	 * @return uint32_t starting sector
	 */
	virtual uint32_t startSector() = 0;
	//Permissions permissons();
};

#endif //EXOS_FSNODE_H
