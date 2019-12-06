ASM = nasm
BOOTSTRAP_FILE = bootstrap.asm 

build: $(BOOTSTRAP_FILE)
	$(ASM) -f bin $(BOOTSTRAP_FILE) -o bootstrap.o
	dd if=bootstrap.o of=kernel.img
	qemu-system-x86_64 kernel.img

clean:
	rm -f *.o
