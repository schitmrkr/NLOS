#include "idt.h"
#include <stdint.h>

#define IDT_ENTRIES 256

extern void idt_load(uint32_t);

static struct idt_entry idt[IDT_ENTRIES];
static struct idt_ptr idtp;

void idt_set_gate(uint8_t num, uint32_t base) {
  idt[num].base_low = base & 0xFFFF;
  idt[num].base_high = (base >> 16) & 0xFFFF;
  idt[num].selector = 0x08; // Kernel code segment
  idt[num].zero = 0;
  idt[num].flags = 0x8E; // 0x8E = 10001110 - present, ring0, interrupt gate
}

void idt_init(void) {
  idtp.limit = sizeof(idt) - 1;
  idtp.base = (uint32_t)&idt;

  for (int i = 0; i < IDT_ENTRIES; i++) {
    idt_set_gate(i, 0);
  }

  idt_load(((uint32_t)&idtp));
}
