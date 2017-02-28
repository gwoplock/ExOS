all:
	if [ -a /mnt/boot/kernel.bin ] ; \
	then \
		rm /mnt/boot/kernel.bin ; \
	fi;

	#rm ./*.o

	nasm /home/garrett/workspace/OS\ C++/src/boot/boot.s -felf -o boot.o
	#/home/garrett/opt/cross/bin/i686-elf-as /home/garrett/workspace/OS/src/ISR/isr_wrapper.s -o isr_wrapper.o 
	/home/garrett/opt/cross/bin/i686-elf-g++ -c /home/garrett/workspace/OS\ C++/src/kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra
	/home/garrett/opt/cross/bin/i686-elf-g++ -c /home/garrett/workspace/OS\ C++/src/memory/GlobalDescriptorTable.cpp -o GDT.o  -ffreestanding -O2 -Wall -Wextra
	/home/garrett/opt/cross/bin/i686-elf-g++ -T /home/garrett/workspace/OS\ C++/linker.ld -o /mnt/usb/boot/kernel.bin -ffreestanding -O2 -nostdlib *.o -lgcc
	sync
