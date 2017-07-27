OBS = boot.o

include ../../makefile.inc


boot.o: $(OS_CPP)/src/boot/boot.s 
	@ nasm $(OS_CPP)/src/boot/boot.s -felf -o $(OBJ_DIR)/boot.o
	
