#include "../include/vga.h"
#include <stdint.h>

static volatile uint16_t *vga_buffer = (uint16_t *)VGA_ADDRESS;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;
static uint8_t current_color = 0x0F;

void vga_clear() {
  uint16_t blank = ((uint16_t)current_color << 8) | (uint8_t)' ';
  for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
    vga_buffer[i] = blank;
  }
  cursor_x = 0;
  cursor_y = 0;
}

uint8_t vga_make_color(uint8_t fg, uint8_t bg) {
  return (bg << 4) | (fg & 0x0F);
}

void vga_set_color(uint8_t color) { current_color = color; }

void vga_putchar(char c) { vga_putchar_color(c, current_color); }

void vga_print(const char *str) { vga_print_color(str, current_color); }

void vga_print_color(const char *str, uint8_t color) {
  for (int i = 0; str[i]; i++) {
    vga_putchar_color(str[i], color);
  }
}

static void vga_scroll() {
  if (cursor_y < VGA_HEIGHT) {
    return;
  }

  for (int row = 1; row < VGA_HEIGHT; row++) {
    for (int col = 0; col < VGA_WIDTH; col++) {
      uint16_t from = row * VGA_WIDTH + col;
      uint16_t to = (row - 1) * VGA_WIDTH + col;
      vga_buffer[to] = vga_buffer[from];
    }
  }

  uint16_t last_row = (VGA_HEIGHT - 1) * VGA_WIDTH;
  for (int col = 0; col < VGA_WIDTH; col++) {
    vga_buffer[last_row + col] = ((uint16_t)current_color << 8) | (uint8_t)' ';
  }

  cursor_y = VGA_HEIGHT - 1;
}

static inline void vga_put_entry_at(char c, uint8_t color, uint8_t x,
                                    uint8_t y) {
  uint16_t index = y * VGA_WIDTH + x;
  vga_buffer[index] = ((uint16_t)color << 8) | (uint8_t)c;
}

void vga_putchar_color(char c, uint8_t color) {
  if (c == '\n') {
    cursor_x = 0;
    cursor_y++;
  } else {
    vga_put_entry_at(c, color, cursor_x, cursor_y);
    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
      cursor_x = 0;
      cursor_y++;
    }
  }
  if (cursor_y >= VGA_HEIGHT) {
    vga_scroll();
  }
}

void vga_set_cursor(uint8_t x, uint8_t y) {
  if (x >= VGA_WIDTH)
    x = VGA_WIDTH - 1;
  if (y >= VGA_HEIGHT)
    y = VGA_HEIGHT - 1;
  cursor_x = x;
  cursor_y = y;
}

void vga_get_cursor(uint8_t *x, uint8_t *y) {
  *x = cursor_x;
  *y = cursor_y;
}
