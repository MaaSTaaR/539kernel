ASM = nasm
CC = gcc
BOOTSTRAP_FILE = bootstrap.asm 
#KERNEL_FILE = simple_kernel.asm
KERNEL_FILES = main.c

# -m32 means generate 32-bit code. See "Machine-Dependent Options" section in gcc man page for details. Under "x86 Options" section "-m flag".
#
# -Wall:
#			"This enables all the warnings about constructions that some
#           users consider questionable, and that are easy to avoid (or
#           modify to prevent the warning), even in conjunction with
#           macros.  This also enables some language-specific warnings
#           described in C++ Dialect Options and Objective-C and
#           Objective-C++ Dialect Options." 
# 			~ GCC man page
# 
# -c:
# 			"If any of these options is used [-c, -S, -E], then the linker is not run, and object file names should not be used as arguments."
# 			~ GCC man page
#
# -ffreestanding:
#			"Assert that compilation targets a freestanding environment.
#           This implies -fno-builtin.  A freestanding environment is one
#           in which the standard library may not exist, and program
#           startup may not necessarily be at "main".  The most obvious
#           example is an OS kernel.  This is equivalent to -fno-hosted."
# 			~ GCC man page
#
# -no-pie:
#			"Don't produce a dynamically linked position independent executable."
# 			~ GCC man page
#
# -g:
#			"To tell GCC to emit extra information for use by a debugger, in almost all cases you need only to add -g to your other options."
# 			~ GCC man page
#
# -std=
#			"Determine the language standard.   This option is currently only supported when compiling C or C++."
#			gnu99: "GNU dialect of ISO C99.  The name gnu9x is deprecated."
#			gnu18: "GNU dialect of ISO C17.  This is the default for C code."
# 			~ GCC man page
#-std=gnu99 # -c -Wall -no-pie -g -std=gnu99
KERNEL_FLAGS = -Wall -m32 -c -ffreestanding -fno-pie -fno-asynchronous-unwind-tables #-S
#  -O1 -fno-pie 
KERNEL_OBJECT = -o kernel.elf
DEBUG = #-S

build: $(BOOTSTRAP_FILE) $(KERNEL_FILE)
	$(ASM) -f bin $(BOOTSTRAP_FILE) -o bootstrap.o
	#$(ASM) -f bin $(KERNEL_FILE) -o kernel.o
	$(CC) $(KERNEL_FLAGS) $(KERNEL_FILES) $(KERNEL_OBJECT)
	#as --32 main.s -o kernel.elf
	objcopy -O binary kernel.elf kernel.o
	dd if=bootstrap.o of=kernel.img
	dd seek=1 conv=sync if=kernel.o of=kernel.img bs=512
	qemu-system-x86_64 $(DEBUG) -s kernel.img

clean:
	rm -f *.o
	rm -f *.elf
	rm -f *.img
