#include "../kernel/arch/x86/io.h"

#include <stdint.h>

// Maps 128 possible PS/2 keyboard scancodes (0x00 - 0x7F) to ascii characters
char scancode_to_ascii[128] = {
    0,    27,   '1',  '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-',
    '=',  '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',  'o', 'p',
    '[',  ']',  '\n', 0, /* 0x0F */
    'a',  's',  'd',  'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z',  'x',  'c', 'v', 'b', 'n', 'm', ',', '.', '/',  0,   '*',
    0,    ' ',  0,    0,   0,   0,   0,   0,   0,   0,   0};

char getkey() {
  uint8_t scancode = 0;
  // keyboard controller status register
  while (!(inb(0x64) & 1)) {
  }
  // keyboard data register
  scancode = inb(0x60);

  // if the scancode is a release code, return 0
  if (scancode & 0x80)
    return 0;
  return scancode_to_ascii[scancode];
}