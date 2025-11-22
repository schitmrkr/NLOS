CC = x86_64-elf-gcc
LD = x86_64-elf-ld
CFLAGS = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -T kernel/link.ld -nostdlib

all: run

build:
	mkdir -p build

build/kernel.o: build kernel/kernel.c
	$(CC) $(CFLAGS) -c kernel/kernel.c -o build/kernel.o

build/boot.o: build kernel/boot.s
	nasm -f elf64 kernel/boot.s -o build/boot.o

build/kernel.elf: build/kernel.o build/boot.o
	$(LD) $(LDFLAGS) -o build/kernel.elf build/kernel.o build/boot.o

iso: build/kernel.elf
	mkdir -p iso/boot/grub
	cp build/kernel.elf iso/boot/
	cp grub/grub.cfg iso/boot/grub/
	x86_64-elf-grub-mkrescue -o nlos.iso iso

run: iso
	qemu-system-x86_64 -cdrom nlos.iso

clean:
	rm -rf build iso nlos.iso
