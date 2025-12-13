#include "../drivers/keyboard.h" // ADD THIS
#include "../drivers/vga.h"
#include "arch/x86/idt.h"
#include "arch/x86/interrupts.h"
#include "arch/x86/io.h"

void kmain() {
  vga_clear();
  pic_remap(); // Must unmask IRQ1 (0xFD → 0xFE)
  idt_init();

  idt_set_gate(0x21, (uint32_t)keyboard_isr); // IRQ1 = INT 33? Wait!

  enable_interrupts();
  vga_print("Type now:\n");

  while (1) {
    char c = getkey(); // REPLACE HLT LOOP
    vga_putchar(c);
  }
}
