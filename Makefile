# Compiler
CC = x86_64-elf-gcc  # Using your existing cross-compiler

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

# Kernel source files (including architecture-specific code and drivers)
KERNEL_SRC = kernel/kernel.c kernel/arch/x86/idt.c kernel/arch/x86/interrupts.c drivers/keyboard.c drivers/vga.c kernel/utils.c kernel/print.c
KERNEL_OBJS = $(KERNEL_SRC:.c=.o)

# Default target
all: kernel.elf

# Link kernel with bootloader and keyboard ISR object
kernel.elf: boot.o $(KERNEL_OBJS) drivers/keyboard_isr.o kernel/arch/x86/idt_load.o
	$(LD) $(LDFLAGS) -T linker.ld -o kernel.elf boot.o $(KERNEL_OBJS) drivers/keyboard_isr.o kernel/arch/x86/idt_load.o

# Assemble bootloader as 32-bit ELF
boot.o: boot/boot.s
	$(AS) -f elf32 boot/boot.s -o boot.o

# Compile kernel C files
kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile architecture-specific C files
kernel/arch/x86/%.o: kernel/arch/x86/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile driver C files
drivers/%.o: drivers/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble driver assembly files (keyboard ISR)
drivers/keyboard_isr.o: drivers/keyboard_isr.s
	$(AS) -f elf32 $< -o $@

# Assemble IDT load routine
kernel/arch/x86/idt_load.o: kernel/arch/x86/idt_load.s
	$(AS) -f elf32 $< -o $@

# Run in QEMU (32-bit)
run: kernel.elf
	qemu-system-i386 -kernel kernel.elf -m 512M -serial stdio

# Clean build artifacts
clean:
	rm -f *.o */arch/x86/*.o *.elf kernel/*.o drivers/*.o
