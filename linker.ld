ENTRY(_start)

SECTIONS
{
    . = 1M;
    . = ALIGN(4096);
    .multiboot : {
        *(.multiboot)
    }
    . = ALIGN(4096);
    .text : {
        *(.text*)
    }
    . = ALIGN(4096);
    .rodata : {
        *(.rodata*)
    }
    . = ALIGN(4096);
    .data : {
        *(.data*)
    }
    . = ALIGN(4096);
    .bss : {
        *(.bss*)
        *(COMMON)
    }

}