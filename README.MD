# ExOS

ExOS extends the [MIT exokernel](https://pdos.csail.mit.edu/archive/exo/) by removing the necessity to relink. Removing this process will allow consumers with no advanced computer knowledge better access to the OS. To achive this, the executable is scanned to identify system calls. Once they are identified, the native OS system calls are replaced with the appropriate ExOS userland system calls (from the LibOS). This replacement process is known as "live relinking".

***Before Working on ExOS, you should have a strong knoledge of the MIT Exokernel.***
 
## Goals

* Working OS  
* LibOSes for all 3 major OSes  
    * Windows  
    * Linux  
    * Mac OS X  
* Live relinking to allow unmodified programs to be run

## Current Status
Ok I gave up on newlib. I have figured out why templates didn't work (you have to extern c for linking those) and I have fixed that. Now we are back on track to get PCI working. 


### What's Left

* ~~Bus enumeration~~
* ~~Device scanning~~
* PCI Config space reading

## Next Steps

* libc (maybe later) (newlib is hard)
* libc++ (maybe later) (needs libc and an os toolchain)
* PCI support (~~waiting for libc(++)~~) (I dont need those so were back to this)
* primitive USB support
* floppy support
* Loading and running programs from disk
* SATA HDD support
* IDE HDD support
* LibOS format
* Live relinking
* Linux LibOS
* Multitasking
* Windows LibOS
   * Possibly based on [ReactOS's](https://www.reactos.org/) code
* Mac OS X LibOS

## Building

### Precompilation steps

1. Build a GCC cross compiler
    * Must be GCC as I use some attributes that are only in GCC.
    * Must be for i686-elf.
    * See [os dev wiki](http://wiki.osdev.org/GCC_Cross-Compiler#Preparing_for_the_build) for more information.
2. Get a bootable medium
    * I'm using a 3.5" floppy but you can use a USB flashdrive or even a CD/DVD.
        * You can also use an emulator such as [Bochs](http://wiki.osdev.org/Bochs) or [QEMU](http://wiki.osdev.org/Qemu) to boot from a disk image.
    * If you're contributing ***please test on real hardware*** not just an emulator.
3. Set up a ***multiboot compliant*** bootloader
    * I'm using [grub legacy](http://wiki.osdev.org/GRUB_Legacy) as my bootloader but you can use whatever as long as it's ***multiboot compliant***.
4. Test the bootloader installation
    * Just boot to the bootloader's menu screen to make sure it works.
5. Configure the makefile
    * I have hard coded in the paths for my compiler toolchain. I have also hard coded the output for the linker to my floppy drive.
        * Will possibly be fixed in the future. You must manually change them to match your system for now.
    
## Compilation

If everything went well in the precompilation stage, running `make all` should work. If you encounter issues at this stage, file an issue with the "bulding" tag (please include the build logs).
