# my-OS

ExoOS extends the [MIT exokernel](https://pdos.csail.mit.edu/archive/exo/) by removing the necessity to relink.  Removing this process will consumers with no computer knowledge access to the OS. To achive this, the executable is scanned to identify system calls.  Once they are identified, the native OS system calls are replaced with ExoOs userland system call in the LibOS. This replacemnt process is known as "Live relinking".

*** Before Working on ExoOs, you should have a strong knoledge of the MIT Exokernel.  !!!
 
## Goals

* Working OS  
* LibOSes for all 3 major OSes  
    * Windows  
    * Linux  
    * Mac OS X  
* Live relinking to allow unmodified programs to be run

## Current Status

so theoretically I am writing the last few things needed to add hard drive support. First one im doing is USB floppy support because that is what im using as the disk with my OS on it. Also because I hate myself

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

1. get yourself a cross compiler
    * must be GCC as I use some attributes in GCC only
    * must be for i686-elf 
    * see [os dev wiki](http://wiki.osdev.org/GCC_Cross-Compiler#Preparing_for_the_build) for more information
2. get some boot media
    * im using a 3.5" floppy but you can use usb or even CDs or DVDs
        * you can also use an emulator such as [Bochs](http://wiki.osdev.org/Bochs) or [QEMU](http://wiki.osdev.org/Qemu)
    * if you're contributing ***please test on real hardware*** not just an emulator
3. set up a ***multiboot compliant*** bootloader
    * I'm using [grub legacy](http://wiki.osdev.org/GRUB_Legacy) as my bootloader but you can use whatever
4. test bootloader installer
    * just boot to the bootloader's menu screen to make sure it works
5. configure the makefile
    * I have hard coded in the paths for my compiler toolchain
    * also I have hard coded the output for the linker to my floppy drive
    * change these to mach your system
    
## Compilation
if everything went well in the precompilation you should just be able to run `make all` and it works. File an issue with the "bulding" tag if there is an issue (please include the build logs)
