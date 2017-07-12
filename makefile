AS = /home/garrett/opt/cross/bin/i686-elf-as
GPP = /home/garrett/opt/cross/bin/i686-elf-g++
GCC = /home/garrett/opt/cross/bin/i686-elf-gcc
OS_CPP = /home/garrett/workspace/OS\ C++
BUILD_TO = /run/media/garrett/disk/boot/kernel.bin
CRTBEGIN_OBJ:=$(shell $(GCC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(GCC) $(CFLAGS) -print-file-name=crtend.o)
OBJS = boot.o isr_wrapper.o Console.o kernel.o GDT.o IDT.o IntHand.o Keyboard.o 
OBJS += ProgrammableInterruptController.o PageTable.o mem.o PageFrameAllocator.o 
OBJS += malloc.o New.o USB.o USBController.o
CFLAGS = -c -ffreestanding -O2 -Wall -Wextra
BOOT = /mnt/boot

boot.o: $(OS_CPP)/src/boot/boot.s 
	nasm $(OS_CPP)/src/boot/boot.s -felf -o boot.o

isr_wrapper.o: $(OS_CPP)/src/interrupts/isr_wrapper.s
	$(AS) $(OS_CPP)/src/interrupts/isr_wrapper.s -o isr_wrapper.o
	
kernel.o: $(OS_CPP)/src/kernel.cpp 
	$(GPP) $(CFLAGS) $(OS_CPP)/src/kernel.cpp -o kernel.o

GDT.o: $(OS_CPP)/src/memory/structures/GlobalDescriptorTable.cpp 
	$(GPP) $(CFLAGS) $(OS_CPP)/src/memory/structures/GlobalDescriptorTable.cpp -o GDT.o
	
IDT.o: $(OS_CPP)/src/interrupts/InterruptDiscriptorTable.cpp 
	$(GPP) $(CFLAGS) $(OS_CPP)/src/interrupts/InterruptDiscriptorTable.cpp -o IDT.o

IntHand.o: $(OS_CPP)/src/interrupts/InteruptHandler.cpp
	$(GPP) $(CFLAGS) $(OS_CPP)/src/interrupts/InteruptHandler.cpp -o IntHand.o
	
ProgrammableInterruptController.o: $(OS_CPP)/src/drivers/ProgrammableInterruptController.cpp
	 $(GPP) $(CFLAGS) $(OS_CPP)/src/drivers/ProgrammableInterruptController.cpp
	 
PageTable.o: $(OS_CPP)/src/memory/structures/PageTable.cpp
	$(GPP) $(CFLAGS) $(OS_CPP)/src/memory/structures/PageTable.cpp

mem.o: $(OS_CPP)/src/memory/mem.cpp
	$(GPP) $(CFLAGS) $(OS_CPP)/src/memory/mem.cpp

PageFrameAllocator.o: $(OS_CPP)/src/memory/alloc/PageFrameAllocator.cpp
	$(GPP) $(CFLAGS) $(OS_CPP)/src/memory/alloc/PageFrameAllocator.cpp

Console.o: $(OS_CPP)/src/drivers/Console.cpp
	$(GPP) $(CFLAGS) $(OS_CPP)/src/drivers/Console.cpp
	
Keyboard.o: $(OS_CPP)/src/drivers/Keyboard.cpp
	$(GPP) $(CFLAGS) $(OS_CPP)/src/drivers/Keyboard.cpp

malloc.o: $(OS_CPP)/src/memory/alloc/malloc.c
	$(GPP) $(CFLAGS) $(OS_CPP)/src/memory/alloc/malloc.c
	
New.o: $(OS_CPP)/src/memory/alloc/New.c
	$(GPP) $(CFLAGS) $(OS_CPP)/src/memory/alloc/New.c
	
USB.o: $(OS_CPP)/src/drivers/PCI/USB/USB.c
	$(GPP) $(CFLAGS) $(OS_CPP)/src/drivers/PCI/USB/USB.c
	
USBController.o: $(OS_CPP)/src/drivers/PCI/USB/USBController.cpp
	$(GPP) $(CFLAGS) $(OS_CPP)/src/drivers/PCI/USB/USBController.cpp

$(BOOT)/kernel.bin: $(OBJS)
	$(GCC) -T $(OS_CPP)/linker.ld -o $(BUILD_TO) -ffreestanding -O2 -nostdlib $(OBJS) -lgcc
	sync

all: $(BOOT)/kernel.bin


clean:
	rm ./*.o
	