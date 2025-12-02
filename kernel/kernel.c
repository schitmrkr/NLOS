#include "../include/print.h"
#include "../include/utils.h"
#include "../include/vga.h"

void kmain(void) {
  uint8_t cyan_on_blue = vga_make_color(VGA_LIGHT_CYAN, VGA_BLUE);
  uint8_t yellow_on_black = vga_make_color(VGA_LIGHT_BROWN, VGA_BLACK);

  vga_set_color(cyan_on_blue);
  vga_clear();

  vga_print_color("Kernel Step 10: Colors & Scrolling\n", cyan_on_blue);
  vga_print_color("Line 1\n", yellow_on_black);
  vga_print_color("Line 2\n", yellow_on_black);
  vga_print_color("Line 3\n", yellow_on_black);

  char buf[12];
  itoa(1234, buf);

  vga_print(buf);
  vga_print("\n");

  kprintf("%d\n", 1234);

  while (1) {
  }
}