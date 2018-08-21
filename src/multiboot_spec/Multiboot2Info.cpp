#include "Multiboot2Info.h"

void Multiboot2Info::build(void* MBI){
	if ((uint64_t)MBI & 7) {
		printf ("Unaligned mbi: 0x%x\n", MBI);
		abort();
	}
	//keeps var size (probly uint32_t)
	uint32_t size = *(uint64_t *) MBI;
	printf("    MBI size = %d \n", size);
	printf ("Announced mbi size 0x%x\n", size);
	for (multiboot_tag * tag = (multiboot_tag *) 
		((uint64_t)MBI + 8); tag->type != MULTIBOOT_TAG_TYPE_END; 
		tag = (multiboot_tag *) ((multiboot_uint8_t *) tag + 
		((tag->size + 7) & ~7))) {
			starts[tag->type]=tag;
	}
}
