AS = i686-elf-as
GPP = i686-elf-g++
GCC = i686-elf-gcc
<<<<<<< HEAD
OS_CPP = /Users/garrettbattaglia/Documents/dev/Exos/exos
BUILD_TO = /Users/garrettbattaglia/Documents/dev/Exos/exos/kernel.bin
CFLAGS = -c -ffreestanding -O2 -Wall -Wextra -fno-rtti -fno-exceptions -g -std=gnu++14 -I$(OS_CPP)/src
=======
OS_CPP = /home/garrett/workspace/ExOS
BUILD_TO = /run/media/garrett/disk/boot/kernel.bin
CFLAGS = -c -ffreestanding -O2 -Wall -Wextra -fno-rtti -fno-exceptions -std=gnu++14 -I$(OS_CPP)/src
>>>>>>> 1181f6b0ac1a30b438dc1b712c846b12dfcb50ab
OBJ_DIR = $(OS_CPP)/build

%.o: %.c
	@ $(GPP) $(CFLAGS) $^ -o $(OBJ_DIR)/$@

%.o: %.cpp
	 @ $(GPP) $(CFLAGS) $^ -o $(OBJ_DIR)/$@

$(SUBDIRS):
	@ $(MAKE) -C $@ all

.PHONY: $(SUBDIRS)

all: $(OBS) $(SUBDIRS)

