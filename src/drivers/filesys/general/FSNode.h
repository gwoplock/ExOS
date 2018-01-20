//
// Created by Garrett Battaglia on 1/20/18.
//

#ifndef EXOS_FSNODE_H
#define EXOS_FSNODE_H

enum Type{
	FILE, DIR, LINK
};

class FSNode{
	private:
		char* _name;
		uint32_t _size;
		FSNode** _children;
		Type _type;
	public:
		uint32_t startSector();
		Permissions permissons();
};

#endif //EXOS_FSNODE_H
