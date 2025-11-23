#include "vga.h"
#include <stdint.h>

// VGA MEMORY starts at 0xB8000 and ends at 0xBFFFF
#define VGA_ADDRESS (unsigned char *)0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static unsigned int cursor = 0;

uint16_t *vga_buffer = (uint16_t *)VGA_ADDRESS;
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

void putchar(char c) {
  if (c == '\n') {
    cursor_x = 0;
    cursor_y++;
  } else {
    uint16_t color = (0x0F << 8); // 0x0F is the color code for white
    vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = color | c;
    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
      cursor_x = 0;
      cursor_y++;
    }
  }
  if (cursor_y >= VGA_HEIGHT) {
    cursor_y = 0;
  }
}

void print(const char *str) {
  // Same as explicit str[i] != '\0'
  for (int i = 0; str[i]; i++) {
    putchar(str[i]);
  }
}

void vga_clear() {
  for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
    vga_buffer[i] = 0;
  }
}

void vga_print(const char *str) {
  unsigned char *vga = VGA_ADDRESS;

  for (unsigned int i = 0; str[i] != '\0'; i++) {
    vga[cursor * 2] = str[i];
    vga[cursor * 2 + 1] = 0x0F;
    cursor++;
  }
}
