#ifndef DRIVERS_DRIVER_BUNDLE_DRIVER_H_
#define DRIVERS_DRIVER_BUNDLE_DRIVER_H_
#include "Global.h"
class Driver{
	private:
		char* provides;
		char* requires;
		Driver* requiresD;
		size_t requiresCount;
		void* elf;
		size_t size;
	public:
		Driver(char* _provides, char* _requires, void* _elf, size_t _size);
		void fillRequires(Driver* drivers, size_t size);
		char* getProvides(){
			return provides;
		}
		char* getRequires(){
			return requires;
		}
		Driver* getRequiresArray(){
			return requiresD;
		}
		size_t getRequiresCount(){
			return requiresCount;
		}
		size_t getSize(){
			return size;
		}
		void* getELF(){
			return elf;
		}
};

#endif