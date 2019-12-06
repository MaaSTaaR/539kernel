ASM = nasm
BOOTSTRAP_FILE = bootstrap.asm 
KERNEL_FILE = kernel.c #simple_kernel.asm

build: $(BOOTSTRAP_FILE) $(KERNEL_FILE)
	$(ASM) -f bin $(BOOTSTRAP_FILE) -o bootstrap.o
	#$(ASM) -f bin $(KERNEL_FILE) -o kernel.o
	#gcc 
	# i686-linux-gnu-gcc-7
	gcc -m32 -c --save-temps $(KERNEL_FILE) -o kernel.o # -g 
	dd if=bootstrap.o of=kernel.img
	dd seek=1 conv=sync if=kernel.o of=kernel.img bs=512
	objcopy --only-keep-debug kernel.o kernel.sym
	qemu-system-x86_64 -s kernel.img # -S

clean:
	rm -f *.o
