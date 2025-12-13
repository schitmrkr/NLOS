#include "keyboard.h"
#include "../kernel/arch/x86/io.h"

static char buffer[256];
static int head = 0, tail = 0;

char scancode_to_ascii[128] = {
    0,    27,   '1', '2',  '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
    '\b', '\t', 'q', 'w',  'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
    '\n', 0,    0,   0,    0,   'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
    ';',  '`',  0,   '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
    0,    0,    0,   0,    ' ', 0,   0,   0,   0,   0,   0,   0};

void keyboard_handler() { // Called by assembly ISR
  uint8_t scancode = inb(0x60);
  if (!(scancode & 0x80) && scancode < 128) {
    char c = scancode_to_ascii[scancode];
    if (c) {
      buffer[head] = c;
      head = (head + 1) % 256;
    }
  }
  outb(0x20, 0x20); // EOI to PIC
}

char getkey() {
  while (head == tail)
    __asm__("hlt");
  char c = buffer[tail];
  tail = (tail + 1) % 256;
  return c;
}
