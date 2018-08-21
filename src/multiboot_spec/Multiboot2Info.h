#include "Global.h"
#include "utils/printf/Printf.h"
#include "Multiboot2.h"

class Multiboot2Info{
	private:
		void* starts[22];
	public:
		Multiboot2Info(){

		}
		Multiboot2Info (void* MBI){
			//NO CONSTRUCTORS ARE RUN... REPLACE WHEN FIXED
			build(MBI);
		}

		void build(void* MBI);
};
