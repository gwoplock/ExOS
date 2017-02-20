################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 

# Each subdirectory must supply rules for building sources it contributes
'/home/garrett/workspace/OS\ C++/Debug/src/asm/boot.o': ../src/asm/boot.s
	@echo 'Building file: $<'
	@echo 'Invoking: Resource Custom Build Step'
	nasm '/home/garrett/workspace/OS C++/src/asm/boot.s' -felf -o '/home/garrett/workspace/OS C++/Debug/src/asm/boot.o'
	@echo 'Finished building: $<'
	@echo ' '


