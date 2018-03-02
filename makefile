all: kernel.bin

SUBDIRS = src

include makefile.inc

kernel.bin: $(SUBDIRS)
	@$(GCC) -T $(OS_CPP)/linker.ld -o $(BUILD_TO) -ffreestanding -O2 -fno-rtti -fno-exceptions -nostartfiles -nostdlib $(OBJ_DIR)/*.o -lgcc

	@sync

clean:
	rm $(OBJ_DIR)/*.o