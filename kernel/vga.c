#include "vga.h"

#define VGA_MEMORY (unsigned char *)0xB8000

static unsigned int cursor = 0;

void vga_print(const char *str) {
  unsigned char *vga = VGA_MEMORY;

  for (unsigned int i = 0; str[i] != '\0'; i++) {
    vga[cursor * 2] = str[i];
    vga[cursor * 2 + 1] = 0x0F;
    cursor++;
  }
}
