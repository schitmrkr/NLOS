BITS 64
GLOBAL start

ALIGN 8
multiboot_header:
    dd 0xE85250D6        ; magic
    dd 0                 ; architecture
    dd 0                 ; length
    dd -(0xE85250D6 + 0) ; checksum

start:
    extern kmain         ; tell NASM this symbol exists in C
    call kmain

.halt:
    jmp .halt            ; infinite loop
