CC = x86_64-elf-gcc
LD = x86_64-elf-ld
AS = nasm

CFLAGS = -ffreestanding -fno-stack-protector -nostdlib -m32
LDFLAGS = -m elf_i386

all: kernel.elf

kernel.elf: boot.o kernel.o vga.o
	$(LD) $(LDFLAGS) -T linker.ld -o kernel.elf boot.o kernel.o vga.o

boot.o: boot/boot.s
	$(AS) -f elf32 boot/boot.s -o boot.o

kernel.o: kernel/kernel.c
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel.o

vga.o: kernel/vga.c
	$(CC) $(CFLAGS) -c kernel/vga.c -o vga.o

run: kernel.elf
	qemu-system-i386 -kernel kernel.elf

clean:
	rm -f *.o *.elf
