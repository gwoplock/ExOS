AS = /home/garrett/opt/cross/bin/i686-elf-as
GPP = /home/garrett/opt/cross/bin/i686-elf-g++
GCC = /home/garrett/opt/cross/bin/i686-elf-gcc
OS_CPP = /home/garrett/workspace/OS\ C++
OBJS = boot.o isr_wrapper.o kernel.o GDT.o IDT.o IntHand.o
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

IntHand.o: $(OS_CPP)/src/interrupts/InteruptHandler.c
	$(GCC) $(CFLAGS) $(OS_CPP)/src/interrupts/InteruptHandler.c -o IntHand.o

$(BOOT)/kernel.bin: $(OBJS)
	$(GCC) -T $(OS_CPP)/linker.ld -o /mnt/usb/boot/kernel.bin -ffreestanding -O2 -nostdlib $(OBJS) -lgcc
	sync

all: $(BOOT)/kernel.bin
	#if [ -a /mnt/boot/kernel.bin ] ; \
	#then \
	#	rm /mnt/boot/kernel.bin ; \
	#fi;

clean:
	rm ./*.o