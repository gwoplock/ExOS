AS = /home/garrett/opt/cross/bin/i686-elf-as
GPP = /home/garrett/opt/cross/bin/i686-elf-g++
GCC = /home/garrett/opt/cross/bin/i686-elf-gcc
OS_CPP = /home/garrett/workspace/ExOS
BUILD_TO = /run/media/garrett/disk/boot/kernel.bin
CFLAGS = -c -ffreestanding -O2 -Wall -Wextra -fno-rtti -fno-exceptions
OBJ_DIR = $(OS_CPP)/build

%.o: %.c
	@ $(GPP) $(CFLAGS) $^ -o $(OBJ_DIR)/$@

%.o: %.cpp
	 @ $(GPP) $(CFLAGS) $^ -o $(OBJ_DIR)/$@

$(SUBDIRS):
	@ $(MAKE) -C $@ all

.PHONY: $(SUBDIRS)

all: $(OBS) $(SUBDIRS)

