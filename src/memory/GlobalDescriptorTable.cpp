/*
 * GlobalDescriptorTable.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */

#include "GlobalDescriptorTable.h"

GlobalDescriptorTable::GlobalDescriptorTable( ) {
	//TODO change flag and access ints into structs
	size = 0;

	AccessU nullAccess;
	nullAccess.accessI = 0;
	FlagsU nullFlags;
	nullFlags.flagsI = 0;
	gdt[size] = encodeGlobalDescriptorTableEntry((uint32_t) 0, (uint32_t) 0,
			nullAccess.accessS, nullFlags.flagsS);

	size++;

	AccessU kernelCodeAccess;
	kernelCodeAccess.accessI = 0x9A;
	FlagsU kernelCodeFlags;
	kernelCodeFlags.flagsI = 0xCF;
	gdt[size] = encodeGlobalDescriptorTableEntry((uint32_t) 0xffffffff,
			(uint32_t) 0, kernelCodeAccess.accessS, kernelCodeFlags.flagsS);
	size++;
	AccessU kernelDataAccess;
	kernelDataAccess.accessI = 0x92;
	FlagsU kernelDataFlags;
	kernelDataFlags.flagsI = 0xCF;
	gdt[size] = encodeGlobalDescriptorTableEntry((uint32_t) 0xffffffff,
			(uint32_t) 0, kernelDataAccess.accessS, kernelDataFlags.flagsS);

	size++;

}

GdtEntry GlobalDescriptorTable::encodeGlobalDescriptorTableEntry(uint32_t limit,
		uint32_t baseAddress, Access access, Flags flags) {
	GdtEntry toRet;
	toRet.access = access;
	toRet.base1 = baseAddress & 0xFFFF;
	toRet.base2 = ( (baseAddress & 0xFF0000) >> 16);
	toRet.base3 = ( (baseAddress & 0xFF000000) >> 24);
	toRet.limit1 = limit & 0xFFFF;
	LimitAndFlags limFlags;
	FlagsU flagsU;
	flagsU.flagsS = flags;
	limFlags.flags = flagsU.flagsI >> 4;
	limFlags.limit = limit;

	toRet.limFlags = limFlags;
	return toRet;
}

