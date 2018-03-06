AS = i686-elf-as
GPP = i686-elf-g++
GCC = i686-elf-gcc


OS_CPP=/home/garrett/workspace/exos
BUILD_TO=/mnt/boot/kernel.bin
#OS_CPP = /Users/garrettbattaglia/Documents/dev/Exos/exos
#BUILD_TO = $(OS_CPP)/kernel.bin
CFLAGS = $(CFLAGS_CUSTOM) -c -ffreestanding -O2 -Wall -Wextra -fno-rtti -fno-exceptions -g -std=gnu++14 -I$(OS_CPP)/src

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

