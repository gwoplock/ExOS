SUBDIRS =
OBS = InterruptDiscriptorTable.o InterruptHandler.o isr_wrapper.o

include ../../makefile.inc

isr_wrapper.o: $(OS_CPP)/src/interrupts/isr_wrapper.s
	 @ $(AS) $(OS_CPP)/src/interrupts/isr_wrapper.s -o $(OBJ_DIR)/isr_wrapper.o
