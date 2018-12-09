#include "LoadBundle.h"
#include "utils/printf/Printf.h"
#include "utils/string/StrLen.h"

// TODO NOTHING IS PAGED IN, NEED TO DO THAT 
void readBootMods(multiboot_info_t* mbi){
	uint32_t count = mbi->mods_count;
	if (count > 0){
			module* modStruct = (module*)(mbi->mods_addr);
			for (unsigned int i = 0; i < count; i++){
				DriverBundle* mod = (DriverBundle*)( modStruct->mod_start);
				if (mod->head.magic == 0xE0DB){
					readDriverBundle(mod);
				} else {
					printf("    WARNING: UNKOWN MODULE FOUND!\n");
				}
			}
	} else {
		printf("no bundle loaded, cant boot! bailing out.");
		abort();
	}
}

void readDriverBundle(DriverBundle* mod){
	for(unsigned int i = 0; i < mod->head.count; i++){
		DriverBundleDriver driver = (&mod->driverBlock)[i];
		auto size = driver.config.Size;
		auto configSize = driver.config.configSize;
		auto providesLength = strlen(driver.config.stringStart) + 1;
		char* provides = malloc(providesLength);
		memcpy(provides, &driver.config.stringStart, providesLength)
		auto requiresLength = strlen((&driver.config.configSize)[providesLength]) + 1;
		char* requires = malloc(requiresLength);
		memcpy(requires, &((&driver.config.configSize)[providesLength]), requiresLength + 1);
	}
}