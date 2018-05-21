#name and versioning
NAME      = ExOS
BIN_NAME  = kernel.bin
VERSION   = 0.0.1A
FULL_NAME = $(NAME)-$(VERSION)
COMMIT    = $(shell  git log -n 1 --format="%h")
TIMESTAMP = $(shell date +'%Y%m%d.%H%M')

#top level dirs
TOPDIR = $(shell git rev-parse --show-toplevel)
SRCDIR = src
OBJDIR = .build

#source files and dirs
SRC_SUBDIRS       = $(shell find $(SRCDIR) -type d -print)
C_SRC_FILES       =  $(foreach dir, $(SRC_SUBDIRS), $(wildcard $(dir)/*.c))
CPP_SRC_FILES     = $(foreach dir, $(SRC_SUBDIRS), $(wildcard $(dir)/*.cpp))
SPECIAL_SRC_FILES = Boot.s ISRWrapper.s

#object files
OBJFILES = $(patsubst %.c,$(OBJDIR)/%.o,$(C_SRC_FILES)) \
$(patsubst %.cpp,$(OBJDIR)/%.o,$(CPP_SRC_FILES)) \
$(OBJDIR)/Boot.o $(OBJDIR)/ISRWrapper.o

#programs
AS    = i686-elf-as
GPP   = i686-elf-g++
GCC   = i686-elf-gcc
MKDIR = mkdir --parents

#flags
INCLUDES = -I$(TOPDIR)/src
LDFLAGS  = -ffreestanding -O2 -fno-rtti -fno-exceptions -nostartfiles -nostdlib -lgcc 
CFLAGS   = -c -ffreestanding -O2 -Wno-packed-bitfield-compat -Wall -Wextra  -fno-rtti -fno-exceptions -g -std=gnu++14 $(INCLUDES)

#Text minip
RED    = $$(tput setaf 1)
BLUE   = $$(tput setaf 4)
GREEN  = $$(tput setaf 2)
WHITE  = $$(tput setaf 7)
YELLOW = $$(tput setaf 3)
BOLD   = $$(tput bold)
NORMAL = $$(tput sgr0)

#verbose option
ifeq ($(VERBOSE), yes)
RUN     =
else
RUN	    = @
VERBOSE = no
endif

#general info
HOSTTYPE = $(shell uname -s)
ifdef MAKECMDGOALS
TARGETGOAL = $(MAKECMDGOALS)
else
TARGETGOAL = $(.DEFAULT_GOAL)
endif


all: warning config $(BIN_NAME) finish

warning:
ifeq ($(VERBOSE),no)
	@echo 
	@echo 'For a more verbose output' 
	@echo '  make '$(GREEN)'VERBOSE=yes' $(NORMAL)$(TARGETGOAL)
	@echo 
endif

config:
	@echo 
	@echo 'TARGET' $(TARGETGOAL)
	@echo 'VERBOSE' $(VERBOSE)
	@echo 
	@echo 'VERSION ' $(VERSION)
	@echo 'COMMIT '$(COMMIT)
	@echo 'DATE ' $(TIMESTAMP)
	@echo 'HOST ' $(HOSTTYPE)
	@echo 

$(BIN_NAME): $(OBJFILES)
ifeq ($(VERBOSE),no)
	@echo 'Constructing' $(RED)$@$(NORMAL)
endif
	$(RUN)$(GCC) -T $(TOPDIR)/linker.ld -o '$@' -ffreestanding -O2 -fno-rtti -fno-exceptions -nostartfiles -nostdlib $(OBJFILES) -lgcc
	@#$(RUN)$(GCC) $(LDFLAGS) -o '$@' $(OBJFILES) $(INCLUDES)

#general rules
$(OBJDIR)/%.o: %.c 
ifeq ($(VERBOSE),no)
	@echo 'Building' $(YELLOW)$<$(NORMAL)
endif
	@test -d $(OBJDIR)/$(dir $<) || $(MKDIR) $(OBJDIR)/$(dir $<)
	$(RUN)$(GPP) -o '$@' $(CFLAGS)  "$<"

$(OBJDIR)/%.o: %.cpp
ifeq ($(VERBOSE),no)
	@echo 'Building' $(YELLOW)$<$(NORMAL)
endif
	@test -d $(OBJDIR)/$(dir $<) || $(MKDIR) $(OBJDIR)/$(dir $<)
	$(RUN)$(GPP) -o '$@' $(CFLAGS)  "$<"


#special rules
$(OBJDIR)/Boot.o: $(TOPDIR)/src/boot/Boot.s 
ifeq ($(VERBOSE),no)
	@echo 'Building' $(YELLOW)$<$(NORMAL)
endif
	@test -d $(OBJDIR)/$(dir $<) || $(MKDIR) $(OBJDIR)/$(dir $<)
	$(RUN)nasm $(TOPDIR)/src/boot/Boot.s -felf -o $(OBJDIR)/Boot.o


$(OBJDIR)/ISRWrapper.o: $(TOPDIR)/src/interrupts/ISRWrapper.s
ifeq ($(VERBOSE),no)
	@echo 'Building' $(YELLOW)$<$(NORMAL)
endif
	@test -d $(OBJDIR)/$(dir $<) || $(MKDIR) $(OBJDIR)/$(dir $<)
	$(RUN)$(AS) $(TOPDIR)/src/interrupts/ISRWrapper.s -o $(OBJDIR)/ISRWrapper.o

finish:
	@echo 'Finished' $(BOLD)$(GREEN)$(TARGETGOAL)$(NORMAL)

clean:
	$(RUN)rm -rf $(OBJDIR)
	$(RUN)rm $(BIN_NAME)
	@echo 'Finished' $(BOLD)$(GREEN)$(TARGETGOAL)$(NORMAL)
	
.PHONY: all warning config clean finish