all:
	if [ -a /run/media/garrett/disk/boot/kernel.bin ] ; \
	then \
		rm /run/media/garrett/disk/boot/kernel.bin ; \
	fi;

	#rm ./*.o

	nasm /home/garrett/workspace/OS\ C++/src/asm/boot.s -felf -o boot.o
	#/home/garrett/opt/cross/bin/i686-elf-as /home/garrett/workspace/OS/src/ISR/isr_wrapper.s -o isr_wrapper.o 
	/home/garrett/opt/cross/bin/i686-elf-gcc -c /home/garrett/workspace/OS\ C++/src/kernel.cpp -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	/home/garrett/opt/cross/bin/i686-elf-gcc -c /home/garrett/workspace/OS\ C++/src/DT/GDT.cpp -o GDT.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	/home/garrett/opt/cross/bin/i686-elf-gcc -T /home/garrett/workspace/OS\ C++/linker.ld -o /run/media/garrett/disk/boot/kernel.bin -ffreestanding -O2 -nostdlib *.o -lgcc
	sync
