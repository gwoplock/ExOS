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
	_gdt[0] = encodeGlobalDescriptorTableEntry((uint32_t) 0x0000F00F,
			(uint32_t) 0x0000B00B, nullAccess.accessS, nullFlags.flagsS);
	terminalWriteString("    ");
	writeInt( *(uint64_t*) &_gdt[0]);
	terminalWriteString("    ");
	BREAKPOINT
	size++;

	AccessU kernelCodeAccess;
	kernelCodeAccess.accessI = 0x9A;
	FlagsU kernelCodeFlags;
	kernelCodeFlags.flagsI = 0xCF;
	_gdt[1] = encodeGlobalDescriptorTableEntry((uint32_t) 0xffffffff,
			(uint32_t) 0, kernelCodeAccess.accessS, kernelCodeFlags.flagsS);
	terminalWriteString("    ");
	writeInt( *(uint64_t*) &_gdt[1]);
	terminalWriteString("    ");
	BREAKPOINT
	size++;
	AccessU kernelDataAccess;
	kernelDataAccess.accessI = 0x92;
	FlagsU kernelDataFlags;
	kernelDataFlags.flagsI = 0xCF;
	_gdt[2] = encodeGlobalDescriptorTableEntry((uint32_t) 0xffffffff,
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

void GlobalDescriptorTable::build( ) {
	//TODO change flag and access ints into structs
	size = 0;

	AccessU nullAccess;
	nullAccess.accessI = 0;
	FlagsU nullFlags;
	nullFlags.flagsI = 0;
	_gdt[0] = encodeGlobalDescriptorTableEntry((uint32_t) 0x0000F00F,
			(uint32_t) 0x0000B00B, nullAccess.accessS, nullFlags.flagsS);
	size++;

	AccessU kernelCodeAccess;
	kernelCodeAccess.accessI = 0x9A;
	FlagsU kernelCodeFlags;
	kernelCodeFlags.flagsI = 0xCF;
	_gdt[1] = encodeGlobalDescriptorTableEntry((uint32_t) 0xffffffff,
			(uint32_t) 0, kernelCodeAccess.accessS, kernelCodeFlags.flagsS);
	size++;
	AccessU kernelDataAccess;
	kernelDataAccess.accessI = 0x92;
	FlagsU kernelDataFlags;
	kernelDataFlags.flagsI = 0xCF;
	_gdt[2] = encodeGlobalDescriptorTableEntry((uint32_t) 0xffffffff,
			(uint32_t) 0, kernelDataAccess.accessS, kernelDataFlags.flagsS);
	size++;

}

