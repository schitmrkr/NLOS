# Compiler
CC = x86_64-elf-gcc

# Linker
LD = x86_64-elf-ld

# Assembler
AS = nasm

# Compiler flags
# -ffreestanding: The code does not use the standard C library
# -fno-stack-protector: Disable stack protection
# -nostdlib: Do not link against the standard C library
# -m32: Generate 32-bit code
# -g: Generate debug information
CFLAGS = -ffreestanding -fno-stack-protector -nostdlib -m32 -g

# Linker flags
# -m elf_i386: Generate 32-bit ELF
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
