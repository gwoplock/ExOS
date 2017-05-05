AS = /home/garrett/opt/cross/bin/i686-elf-as
GPP = /home/garrett/opt/cross/bin/i686-elf-g++
GCC = /home/garrett/opt/cross/bin/i686-elf-gcc
OS_CPP = /home/garrett/workspace/OS\ C++
OBJS = boot.o isr_wrapper.o Console.o kernel.o GDT.o IDT.o IntHand.o ProgrammableInterruptController.o PageTable.o mem.o PageFrameAllocator.o
CFLAGS = -c -ffreestanding -O2 -Wall -Wextra
BOOT = /mnt/boot

boot.o: $(OS_CPP)/src/boot/boot.s 
	nasm $(OS_CPP)/src/boot/boot.s -felf -o boot.o

isr_wrapper.o: $(OS_CPP)/src/interrupts/isr_wrapper.s
	$(AS) $(OS_CPP)/src/interrupts/isr_wrapper.s -o isr_wrapper.o
	
kernel.o: $(OS_CPP)/src/kernel.cpp $(OS_CPP)/src/kernel.h
	$(GPP) $(CFLAGS) $(OS_CPP)/src/kernel.cpp -o kernel.o

GDT.o: $(OS_CPP)/src/memory/GlobalDescriptorTable.cpp $(OS_CPP)/src/memory/GlobalDescriptorTable.h
	$(GPP) $(CFLAGS) $(OS_CPP)/src/memory/GlobalDescriptorTable.cpp -o GDT.o
	
IDT.o: $(OS_CPP)/src/interrupts/InterruptDiscriptorTable.cpp $(OS_CPP)/src/interrupts/InterruptDiscriptorTable.h
	$(GPP) $(CFLAGS) $(OS_CPP)/src/interrupts/InterruptDiscriptorTable.cpp -o IDT.o

IntHand.o: $(OS_CPP)/src/interrupts/InteruptHandler.cpp
	$(GPP) $(CFLAGS) $(OS_CPP)/src/interrupts/InteruptHandler.cpp -o IntHand.o
	
ProgrammableInterruptController.o: $(OS_CPP)/src/drivers/ProgrammableInterruptController.cpp
	 $(GPP) $(CFLAGS) $(OS_CPP)/src/drivers/ProgrammableInterruptController.cpp
	 
PageTable.o: $(OS_CPP)/src/memory/PageTable.cpp
	$(GPP) $(CFLAGS) $(OS_CPP)/src/memory/PageTable.cpp

mem.o: $(OS_CPP)/src/memory/mem.cpp
	$(GPP) $(CFLAGS) $(OS_CPP)/src/memory/mem.cpp

PageFrameAllocator.o: $(OS_CPP)/src/memory/PageFrameAllocator.cpp
	$(GPP) $(CFLAGS) $(OS_CPP)/src/memory/PageFrameAllocator.cpp

Console.o: $(OS_CPP)/src/drivers/Console.cpp
	$(GPP) $(CFLAGS) $(OS_CPP)/src/drivers/Console.cpp

$(BOOT)/kernel.bin: $(OBJS)
	$(GCC) -T $(OS_CPP)/linker.ld -o /run/media/garrett/disk/boot/kernel.bin -ffreestanding -O2 -nostdlib $(OBJS) -lgcc
	sync

all: $(BOOT)/kernel.bin
	#if [ -a /mnt/boot/kernel.bin ] ; \
	#then \
	#	rm /mnt/boot/kernel.bin ; \
	#fi;

clean:
	rm ./*.o