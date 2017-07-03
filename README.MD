# my-OS

This operating system is based around the [MIT exokernel](https://pdos.csail.mit.edu/archive/exo/) but expands it to consumers with no computer knowledge. The idea is to read through the executable for the system calls and replace them with a user land system call from the LibOS for the OS the program should be running under. Im calling this replacemnt process "Live relinking". 
 
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

## Make Dependencies
* compiler toolchain for i686-elf

## Compilation

set the final build path in the linker to whatever you're using. then: 

    make
