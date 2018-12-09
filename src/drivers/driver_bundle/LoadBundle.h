#ifndef DRIVERS_DRIVER_BUNDLE_LOAD_BUNDLE_H_
#define DRIVERS_DRIVER_BUNDLE_LOAD_BUNDLE_H_
#include "Global.h"
#include "multiboot_spec/Multiboot.h"

struct DriverBundleHeader{
	uint16_t magic;
	uint32_t count;
}__attribute__((__packed__));

struct DriverBundleDriverConfig{
	uint32_t Size;
	uint32_t configSize;
	char stringStart;
}__attribute__((__packed__));

struct DriverBundleDriver{
	DriverBundleDriverConfig config;
	uint32_t elfMagic;
}__attribute__((__packed__));

struct DriverBundle{
DriverBundleHeader head;
DriverBundleDriver driverBlock;
}__attribute__((__packed__));

void readBootMods(multiboot_info_t* );

void readDriverBundle(DriverBundle* mod);


#endif