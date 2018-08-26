#include "Global.h"
#include "utils/printf/Printf.h"
#include "Multiboot2.h"

class Multiboot2Info{
	private:
		
	public:
		Multiboot2Info(){

		}
		Multiboot2Info (void* MBI){
			//NO CONSTRUCTORS ARE RUN... REPLACE WHEN FIXED
			build(MBI);
		}

		void build(void* MBI);
		void* get(uint32_t tag);
};
