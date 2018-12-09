#include "LoadBundle.h"
#include "utils/printf/Printf.h"
#include "utils/string/StrLen.h"
#include "Kernel.h"
#include "memory/structures/PageTable.h"
#include "memory/alloc/PageFrameAllocator.h"

// TODO NOTHING IS PAGED IN, NEED TO DO THAT 
void readBootMods(multiboot_info_t* mbi){
	mbi = (multiboot_info_t*) ((int32_t) mbi + (uint32_t) pageTable.getKernelStart());
	uint32_t count = mbi->mods_count;
	if (count > 0){
			module* modStruct = (module*)(mbi->mods_addr + (uint32_t) pageTable.getKernelStart());
			for (unsigned int i = 0; i < count; i++){
				DriverBundle* mod = (DriverBundle*)( modStruct->mod_start);
				auto nextAddr = frameAlloc.getNextVirtAddr(1, pageTable.getKernelStart());
				mod = (DriverBundle*)pageTable.page(mod, nextAddr, FOUR_KB);
				if (mod->head.magic == 0xDBE0){
					readDriverBundle(mod);
				} else {
					printf("    WARNING: UNKOWN MODULE FOUND! magic number = %x\n", mod->head.magic);
				}
			}
	} else {
		printf("no bundle loaded, cant boot! bailing out.");
		abort();
	}
}

DriverArr readDriverBundle(DriverBundle* mod){
	DriverArr toRet;
	BREAKPOINT
	printf("count = %d", mod->head.count );
	toRet.drivers = (Driver*) malloc(mod->head.count * sizeof(Driver));
	BREAKPOINT
	for(unsigned int i = 0; i < mod->head.count; i++){
		DriverBundleDriver driver = (&mod->driverBlock)[i];
		auto size = driver.config.Size;
		auto configSize = driver.config.configSize;
		auto providesLength = strlen(&driver.config.stringStart) + 1;
		BREAKPOINT
		char* provides = (char*)malloc(providesLength);
		memcpy(provides, &driver.config.stringStart, providesLength);
		BREAKPOINT
		auto requiresLength = strlen(&((&driver.config.stringStart)[providesLength])) + 1;
		BREAKPOINT
		char* requires = (char*)malloc(requiresLength);
		memcpy(requires, &((&driver.config.configSize)[providesLength]), requiresLength + 1);
		BREAKPOINT
		toRet.drivers[i] = Driver(provides, requires, (void*)&(driver.elfMagic), size);
		BREAKPOINT
	}
	return toRet;
}