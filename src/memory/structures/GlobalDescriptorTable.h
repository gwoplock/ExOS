/*
 * GlobalDescriptorTable.h
 *
 *  Created on: Feb 20, 2017
 *      Author: garrett
 */

#ifndef GLOBALDESCRIPTORTABLE_H_
#define GLOBALDESCRIPTORTABLE_H_
//#include "../../drivers/Console.h"
#include "../../Global.h"



struct Flags {
		uint8_t zero : 6;
		uint8_t size : 1;
		uint8_t granularity :1;

}__attribute__((packed));
struct Access {
		uint8_t accessed :1;
		uint8_t readWrite :1;
		uint8_t direction :1;
		uint8_t exicute :1;
		uint8_t one :1;
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
		GdtEntry* location;
}__attribute__((packed));
class GlobalDescriptorTable {
	private:
		/**
		 * the actual gdt
		 */
		GdtEntry _gdt[256];
		/**
		 * length of gdt
		 */
		size_t size;
		/**
		 * the structure that the gdt reads
		 */
		GdtDescriptor gdtd;
	public:
		GlobalDescriptorTable( ) ;
		//GlobalDescriptorTable( const GlobalDescriptorTable &) = delete;
		//auto operator= (const GlobalDescriptorTable &) = delete;
		/**
		 * encode gdt entry
		 * @param limit
		 * @param base Address
		 * @param access
		 * @param flags
		 * @return encoded GDT entry
		 */
		GdtEntry encodeGlobalDescriptorTableEntry(uint32_t limit,
				uint32_t baseAddress, Access access, Flags flags);
		/**
		 * load the GDT into the cpu
		 */
		void load( ) {
			//get size, -1 because Int-hell hates you
			size_t sizeOfGdt = (size * sizeof(GdtEntry)) - 1;
			//get the info to tell cpu about the GDT
			gdtd.size = (uint16_t)sizeOfGdt;
			gdtd.location = &_gdt[0];
			asm ("LGDT %[gdtd]" : : [gdtd] "m" (gdtd));
		}
		void build();
};

#endif /* GLOBALDESCRIPTORTABLE_H_ */
