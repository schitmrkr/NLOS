CC = x86_64-elf-gcc
LD = x86_64-elf-ld
AS = nasm

CFLAGS = -ffreestanding -fno-stack-protector -nostdlib -m32 -g
LDFLAGS = -m elf_i386

KERNEL_SRC = kernel/kernel.c kernel/vga.c kernel/utils.c
KERNEL_OBJS = $(KERNEL_SRC:.c=.o)

all: kernel.elf

kernel.elf: boot.o $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) -T linker.ld -o kernel.elf boot.o $(KERNEL_OBJS)

# Assemble bootloader
boot.o: boot/boot.s
	$(AS) -f elf32 boot/boot.s -o boot.o

# Compile kernel C files
kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run in QEMU
run: kernel.elf
	qemu-system-i386 -kernel kernel.elf

# Clean build artifacts
clean:
	rm -f *.o *.elf kernel/*.o
