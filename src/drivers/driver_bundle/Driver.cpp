#include "Driver.h"

Driver::Driver(char* _provides, char* _requires, void* _elf, size_t _size){
	provides = _provides;
	requires = _requires;
	size = _size;
	elf = _elf;
}