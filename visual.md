Power On / BIOS
    |
    v
Bootloader (GRUB)
    |
    v
Load kernel.elf into memory
    |
    v
Jump to _start
    |
    v
Call kmain() → Your kernel code runs
    |
    v
Write to VGA, handle hardware, etc.
