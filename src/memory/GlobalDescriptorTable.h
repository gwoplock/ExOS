/*
 * GlobalDescriptorTable.h
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */

#ifndef GLOBALDESCRIPTORTABLE_H_
#define GLOBALDESCRIPTORTABLE_H_

#include "../global.h"
struct Flags {
		uint8_t zero : 5;
		uint8_t size : 1;
		uint8_t Granularity :1;

}__attribute__((packed));
struct Access {
		uint8_t accessed :1;
		uint8_t readWrite :1;
		uint8_t direction :1;
		uint8_t exicute :1;
		uint8_t privilge :2;
		uint8_t present :1;
}__attribute__((packed));
struct LimitAndFlags {
		uint8_t limit:4;
		uint8_t flags:4;
}__attribute__((packed));
struct GdtEntry {
		uint16_t limit1;
		uint16_t base1;
		uint8_t base2;
		Access access;
		LimitAndFlags limFlags;
		uint8_t base3;
}__attribute__((packed));
union GdtEntryU {
		GdtEntry entryS;
		uint32_t entryI;
};
union LimitAndFlagsU {
		LimitAndFlags limFlagsS;
		uint8_t limFlagsI;
};
union AccessU {
		Access accessS;
		uint8_t accessI;
};
union FlagsU {
		Flags flagsS;
		uint8_t flagsI;
};
struct GdtDescriptor {
		uint16_t size;
		uint32_t location;
}__attribute__((packed));
class GlobalDescriptorTable {
	private:
		GdtEntry gdt[256];
		size_t size;
		GdtDescriptor gdtd;
	public:
		GlobalDescriptorTable( ) ;
		GdtEntry encodeGlobalDescriptorTableEntry(uint32_t limit,
				uint32_t baseAddress, Access access, Flags flags);
		void load( ) {
			//get size, -1 because Int-hell hates you
			size_t sizeOfGdt = size * sizeof(GdtEntry) - 1;
			//get the info to tell cpu about the GDT

			gdtd.size = sizeOfGdt;
			gdtd.location = (uint32_t) gdt;
			//load that shit
			asm ("LGDT %[gdt]" : : [gdt] "m" (gdtd));
		}
};

#endif /* GLOBALDESCRIPTORTABLE_H_ */
