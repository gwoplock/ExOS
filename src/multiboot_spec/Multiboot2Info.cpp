#include "Multiboot2Info.h"
#include "memory/structures/PageTable.h"

void* starts[22];

//TODO clean up paging math
void Multiboot2Info::build(void* MBI){
	pageTable.page(MBI, (void*)((uint32_t)pageTable.getKernelStart() + (uint32_t)MBI) , 4);
	MBI = (void*)(((uint64_t)MBI) + (uint32_t)pageTable.getKernelStart());
	printf("\n      MBI  = 0x%x\n", MBI);
	if ((uint64_t)MBI & 7) {
		printf ("      Unaligned mbi: 0x%x\n", MBI);
		abort();
	}
	//keeps var size (probly uint32_t)
	uint32_t size = *(uint64_t *) MBI;
	printf("      MBI size = %d \n", size);
	MBI = (void*)(((uint64_t)MBI) - (uint32_t)pageTable.getKernelStart());
	pageTable.page(MBI, (void*)((uint32_t)pageTable.getKernelStart() + (uint32_t)MBI) , size+ FOUR_KB);
	MBI = (void*)(((uint64_t)MBI) + (uint32_t)pageTable.getKernelStart());
	for (multiboot_tag * tag = (multiboot_tag *) 
		(((uint64_t)MBI) + 8); ; 
		tag = (multiboot_tag *) ((multiboot_uint8_t *) tag + 
		((tag->size + 7) & ~7))) {
			printf("      tag = 0x%x\n", tag);
			if (tag->type == MULTIBOOT_TAG_TYPE_END){
				break;
			}
			printf("      assining tag 0x%x (size %d) to 0x%x (type %d) \n", tag, tag->size, &starts[tag->type],tag-> type);

			starts[tag->type]=tag;
	}
}

void* Multiboot2Info::get(uint32_t tag){
	return starts[tag];
}
