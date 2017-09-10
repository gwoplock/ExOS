OBS = Boot.o

include ../../makefile.inc


Boot.o: $(OS_CPP)/src/boot/Boot.s 
	@ nasm $(OS_CPP)/src/boot/Boot.s -felf -o $(OBJ_DIR)/Boot.o
	
