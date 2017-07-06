# ExOS

ExOS extends the [MIT exokernel](https://pdos.csail.mit.edu/archive/exo/) by removing the necessity to relink. Removing this process will allow consumers with no advanced computer knowledge better access to the OS. To achive this, the executable is scanned to identify system calls. Once they are identified, the native OS system calls are replaced with the appropriate ExOS userland system call (located in the LibOSes). This replacement process is known as "Live relinking".

***Before Working on ExOS, you should have a strong knoledge of the MIT Exokernel.***
 
## Goals

* Working OS  
* LibOSes for all 3 major OSes  
    * Windows  
    * Linux  
    * Mac OS X  
* Live relinking to allow unmodified programs to be run

## Current Status

Currently I am writing the last few process needed for hard drive support. We are starting with USB floppy support because of the flexibility for development.

### What's Left
* basic USB support
* floppy support


## Next Steps

* ~~libc~~ (maybe later)
* ~~libc++~~ (maybe later)
* USB floppy support    
* Program Loading and running  
* SATA HDD support  
* IDE HDD support 
* LibOS format
* Live relinking
* Linux LibOS
* Multitasking
* Windows LibOS
   * Possibly based on react OS's code
* Mac OS X LibOS

## Building

### Precompilation steps

1. Build a GCC cross compiler
    * must be GCC as I use some attributes that are only in GCC
    * must be for i686-elf 
    * see [os dev wiki](http://wiki.osdev.org/GCC_Cross-Compiler#Preparing_for_the_build) for more information
2. Get a bootable medium
    * I'm using a 3.5" floppy but you can use a USB flashdrive or even a CD/DVD
        * You can also use an emulator such as [Bochs](http://wiki.osdev.org/Bochs) or [QEMU](http://wiki.osdev.org/Qemu) to boot from a disk image.
    * If you're contributing ***please test on real hardware*** not just an emulator.
3. Set up a ***multiboot compliant*** bootloader
    * I'm using [grub legacy](http://wiki.osdev.org/GRUB_Legacy) as my bootloader but you can use whatever as long as it's ***multiboot compliant***.
4. Test the bootloader installation
    * Just boot to the bootloader's menu screen to make sure it works.
5. Configure the makefile
    * I have hard coded in the paths for my compiler toolchain. I have also hard coded the output for the linker to my floppy drive.
        * Change them to mach your system.
    
## Compilation

If everything went well in the precompilation stage, running `make all` and should work. If you entounter issues at this stage, file an issue with the "bulding" tag (please include the build logs)
