#include "print.h"
#include "utils.h"
#include "vga.h"
#include <stdarg.h>

void kprintf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  char buf[32];

  // fmt[i] is equivalent to *(fmt + i)
  for (int i = 0; fmt[i]; i++) {
    if (fmt[i] == '%') {
      i++;
      switch (fmt[i]) {
      case 'd': {
        int val = va_arg(args, int);
        itoa(val, buf);
        vga_print(buf);
        break;
      }
      case 'x': {
        unsigned int val = va_arg(args, unsigned int);
        itox(val, buf);
        vga_print(buf);
        break;
      }
      case 's': {
        char *val = va_arg(args, char *);
        vga_print(val);
        break;
      }
      case '%': {
        vga_putchar('%');
        break;
      }
      default: {
        vga_putchar('%');
        vga_putchar(fmt[i]);
      }
      }
    } else {
      vga_putchar(fmt[i]);
    }
  }

  va_end(args);
}