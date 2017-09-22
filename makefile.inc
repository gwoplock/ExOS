AS = i686-elf-as
GPP = i686-elf-g++
GCC = i686-elf-gcc
OS_CPP = /home/garrett/workspace/ExOS
BUILD_TO = /run/media/garrett/EXOS/boot/kernel.bin
CFLAGS = -c -ffreestanding -O2 -Wall -Wextra -fno-rtti -fno-exceptions -std=gnu++14 -I$(OS_CPP)/src
OBJ_DIR = $(OS_CPP)/build
LINK_FLAGS = -ffreestanding -O2 -fno-rtti -fno-exceptions -nostartfiles -nostdlib

%.o: %.c
	@ $(GPP) $(CFLAGS) $^ -o $(OBJ_DIR)/$@

%.o: %.cpp
	 @ $(GPP) $(CFLAGS) $^ -o $(OBJ_DIR)/$@

$(SUBDIRS):
	@ $(MAKE) -C $@ all

.PHONY: $(SUBDIRS)

all: $(OBS) $(SUBDIRS)

