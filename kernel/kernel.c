#include "vga.h"

void kmain() {
  vga_clear();
  print("Hello QEMU!\n");
  while (1) {
  }
}