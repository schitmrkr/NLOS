; ===== Multiboot header (NASM syntax) =====

MAGIC     equ 0x1BADB002
FLAGS     equ 0x00000003
CHECKSUM  equ -(MAGIC + FLAGS)

section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; ===== Code Section =====

section .text
global _start

_start:
    ; Call kmain()
    extern kmain
    call kmain

.hang:
    jmp .hang
