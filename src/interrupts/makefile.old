SUBDIRS =
OBS = InterruptDescriptorTable.o InterruptHandler.o ISRWrapper.o

include ../../makefile.inc

ISRWrapper.o: $(OS_CPP)/src/interrupts/ISRWrapper.s
	 @ $(AS) $(OS_CPP)/src/interrupts/ISRWrapper.s -o $(OBJ_DIR)/ISRWrapper.o
